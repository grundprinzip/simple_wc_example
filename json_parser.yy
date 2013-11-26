%skeleton "lalr1.cc"
%require  "3.0"
%debug 
%defines 
%define api.namespace {JSON}
%define parser_class_name {JsonParser}

%define api.token.constructor
%define api.value.type variant
//%define parse.assert


%code requires{
  
   namespace JSON {
      class JsonDriver;
      class JsonParser;      
   }

   #include "json_st.hh"
}

%param { JsonDriver &driver }

%locations
%code{
   #include <iostream>
   #include <cstdlib>
   #include <fstream>
   
   /* include for all driver functions */
   #include "json_driver.hpp"   
   #include "json_st.hh"
  

}

/* token types */

%token            END    0     "end of file"

%token <std::string> JSON_STRING
%token <long> JSON_INT
%token <double> JSON_DOUBLE
%token <bool> JSON_TRUE
%token <bool> JSON_FALSE
%token JSON_NULL
%token SQUARE_BRACKET_L SQUARE_BRACKET_R
%token CURLY_BRACKET_L CURLY_BRACKET_R
%token COMMA COLON

/** Types used to identify the actual values **/
%type <JSON::Value> JsonObject JsonValue
%type <JSON::Value> JsonMap JsonMapValueList
%type <JSON::Value> JsonArray JsonArrayValueList

%%

%start JsonObject;

JsonObject              :   JsonMap                                 { 
                            driver.result = std::move($1); driver.log("JsonObject: JsonMap");
                         }
                        |   JsonArray                               { 
                           driver.result = std::move($1); driver.log("JsonObject: JsonArray");
                        }
JsonMap                 :   CURLY_BRACKET_L JsonMapValueList CURLY_BRACKET_R  { 
                            $$ = std::move($2); driver.log("JsonMap: { JsonMapValueList }");
                         }

JsonMapValueList        : /* empty */ { $$ = JSON::Value(JSON::OBJECT); }  
                        |  JSON_STRING COLON JsonValue                            { 
                           $$ = JSON::Value(JSON::OBJECT); 
                           $$.emplace(std::move($1), std::move($3));
                           driver.log("JsonMapValueList: JsonMapValue"); 
                        } 
                        |  JsonMapValueList COMMA JSON_STRING COLON JsonValue     {
                           $1.emplace(std::move($3), std::move($5));
                           $$ = std::move($1);
                           driver.log("JsonMapValueList: JsonMapValueList , JsonMapValue");
                        }

JsonArray               :   SQUARE_BRACKET_L JsonArrayValueList SQUARE_BRACKET_R  { $$ = std::move($2); driver.log("JsonArray: [ JsonArrayValueList ]");}

JsonArrayValueList      :   /* empty */ { 
                           $$ = JSON::Value(JSON::ARRAY); 
                        }
                        | JsonValue                               { 
                           $$ = JSON::Value(JSON::ARRAY);
                           $$.push_back(std::move($1)); 
                           driver.log("JsonArrayValueList: JsonValue"); 
                        }
                        | JsonArrayValueList COMMA JsonValue        {
                           $1.push_back(std::move($3));
                           $$ = std::move($1);
                           driver.log("JsonArrayValueList: JsonArrayValueList , JsonValue");
                        }

JsonValue               :   JsonMap                                 { $$ = std::move($1); driver.log("JsonValue: JsonMap");}
                        |   JsonArray                               { $$ = std::move($1); driver.log("JsonValue: JsonArray");}
                        |   JSON_STRING                             { $$ = std::move(JSON::Value($1)); driver.log("JsonValue: JSON_STRING");}
                        |   JSON_INT                                { $$ = std::move(JSON::Value($1)); driver.log("JsonValue: JSON_INT ", $1);}
                        |   JSON_DOUBLE                             { $$ = std::move(JSON::Value($1)); driver.log("JsonValue: JSON_DOUBLE");}
                        |   JSON_TRUE                               { $$ = std::move(JSON::Value($1)); driver.log("JsonValue: JSON_TRUE");}
                        |   JSON_FALSE                              { $$ = std::move(JSON::Value($1)); driver.log("JsonValue: JSON_FALSE");}
                        |   JSON_NULL                               { $$ = std::move(JSON::Value()); driver.log("JsonValue: JSON_NULL");}

%%

void 
JSON::JsonParser::error( const JsonParser::location_type& l, const std::string &err_message )
{
   std::cerr << "Error: " << err_message << " " << l << "\n"; 
}

