%skeleton "lalr1.cc"
%require  "3.0"
%debug 
%defines 
%define api.namespace {JSON}
%define parser_class_name {MC_Parser}

%code requires{
   namespace JSON {
      class MC_Driver;
      class MC_Scanner;
   }
}

%lex-param   { MC_Scanner  &scanner  }
%parse-param { MC_Scanner  &scanner  }

%lex-param   { MC_Driver  &driver  }
%parse-param { MC_Driver  &driver  }

%code{
   #include <iostream>
   #include <cstdlib>
   #include <fstream>
   
   /* include for all driver functions */
   #include "json_driver.hpp"
  
   /* this is silly, but I can't figure out a way around */
   static int yylex(JSON::MC_Parser::semantic_type *yylval,
                    JSON::MC_Scanner  &scanner,
                    JSON::MC_Driver   &driver);
   
}

/* token types */
%union {
   std::string *sval;
}

%token            END    0     "end of file"
%token            UPPER
%token            LOWER
%token   <sval>   WORD
%token            NEWLINE
%token            CHAR


/* destructor rule for <sval> objects */
%destructor { if ($$)  { delete ($$); ($$) = nullptr; } } <sval>


%%

list_option : END | list END;

list
  : item
  | list item
  ;

item
  : UPPER   { driver.add_upper(); }
  | LOWER   { driver.add_lower(); }
  | WORD    { driver.add_word( *$1 ); }
  | NEWLINE { driver.add_newline(); }
  | CHAR    { driver.add_char(); }
  ;

%%


void 
JSON::MC_Parser::error( const std::string &err_message )
{
   std::cerr << "Error: " << err_message << "\n"; 
}


/* include for access to scanner.yylex */
#include "json_scanner.hpp"
static int 
yylex( JSON::MC_Parser::semantic_type *yylval,
       JSON::MC_Scanner  &scanner,
       JSON::MC_Driver   &driver )
{
   return( scanner.yylex(yylval) );
}

