%skeleton "lalr1.cc"
%require  "3.0"
%debug 
%defines 
%define api.namespace {JSON}
%define parser_class_name {JsonParser}

%define api.token.constructor
%define api.value.type variant
%define parse.assert


%code requires{
  
   namespace JSON {
      class JsonDriver;
      class JsonParser;      
   }

}

%param { JsonDriver &driver }

%locations
%code{
   #include <iostream>
   #include <cstdlib>
   #include <fstream>
   
   /* include for all driver functions */
   #include "json_driver.hpp"   

}

/* token types */

%token            END    0     "end of file"
%token            UPPER
%token            LOWER
%token   <std::string>   WORD
%token            NEWLINE
%token            CHAR



%%

list_option : END | list END;

list
  : item
  | list item
  ;

item
  : UPPER   { driver.add_upper(); }
  | LOWER   { driver.add_lower(); }
  | WORD    { driver.add_word( $1 ); }
  | NEWLINE { driver.add_newline(); }
  | CHAR    { driver.add_char(); }
  ;

%%

void 
JSON::JsonParser::error( const JsonParser::location_type& l, const std::string &err_message )
{
   std::cerr << "Error: " << err_message << "\n"; 
}

