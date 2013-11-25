%{
/* C++ string header, for string ops below */
#include <string>
/* Implementation of yyFlexScanner */ 
#include "json_scanner.hpp"

using namespace std;

/* typedef to make the returns for the tokens shorter */
typedef JSON::MC_Parser::token token;

/* define to keep from re-typing the same code over and over */
#define STOKEN( x ) ( new std::string( x ) )

/* define yyterminate as this instead of NULL */
#define yyterminate() return( token::END )

/* msvc2010 requires that we exclude this header file. */
#define YY_NO_UNISTD_H

%}

%option debug 
%option nodefault 
%option yyclass="MC_Scanner" 
%option noyywrap 
%option c++

%%
[a-z]       { 
               return( token::LOWER );     
            }

[A-Z]       { 
               return( token::UPPER );     
            }

[a-zA-Z]+   { 
               yylval->sval = STOKEN( yytext );  
               return( token::WORD );      
            }

\n          { 
               return( token::NEWLINE );   
            }

.           { 
               return( token::CHAR );      
            }
%%


