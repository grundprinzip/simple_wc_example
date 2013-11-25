%{
/* C++ string header, for string ops below */
#include <string>
#include <cstring>
#include <cerrno>
#include <stdexcept>

#include "json_driver.hpp"
#include "json_parser.tab.hh"


using namespace std;

/* define yyterminate as this instead of NULL */
#define yyterminate() return( JSON::JsonParser::make_END(loc) )

// The location of the current token.
static JSON::JsonParser::location_type loc;

%}

%option debug 
%option batch
%option nodefault 
%option noyywrap 


%%
[a-z]       { 
               return JSON::JsonParser::make_LOWER(loc);
            }

[A-Z]       { 
               return JSON::JsonParser::make_UPPER(loc);     
            }

[a-zA-Z]+   { 
               return JSON::JsonParser::make_WORD(yytext, loc);               
            }

\n          { 
               return JSON::JsonParser::make_NEWLINE(loc);   
            }

.           { 
               return JSON::JsonParser::make_CHAR(loc);      
            }
%%


void
JSON::JsonDriver::prepare_string(const std::string data) {
  yy_flex_debug = trace_scanning;
  yy_scan_string(data.c_str());
}