%{
/* C++ string header, for string ops below */
#include <string>
#include <cstring>
#include <cerrno>
#include <climits>
#include <cstdlib>
#include <stdexcept>

#include "json_driver.hpp"
#include "json_parser.tab.hh"


using namespace std;

/* define yyterminate as this instead of NULL */
#define yyterminate() return( JSON::JsonParser::make_END(loc) )

// The location of the current token.
static JSON::JsonParser::location_type loc;

%}

%option batch
%option nodefault 
%option noyywrap 

DIGIT           [0-9]
DIGIT1          [1-9]
INTNUM          -?{DIGIT1}{DIGIT}*
FRACT           "."{DIGIT}+
FLOAT           ({INTNUM}|0){FRACT}{EXP}?
EXP             [eE][+-]?{DIGIT}+

UNICODE         \\u[A-Fa-f0-9]{4}
ESCAPECHAR      \\["\\/bfnrt]
CHAR            [^"\\]|{ESCAPECHAR}|{UNICODE}
STRING          \"{CHAR}*\"

WHITESPACE      [ \t\n]

%%

\{              {return JSON::JsonParser::make_CURLY_BRACKET_L(loc);}
\}              {return JSON::JsonParser::make_CURLY_BRACKET_R(loc);}
\[              {return JSON::JsonParser::make_SQUARE_BRACKET_L(loc);}
\]              {return JSON::JsonParser::make_SQUARE_BRACKET_R(loc);}
,               {return JSON::JsonParser::make_COMMA(loc);}
:               {return JSON::JsonParser::make_COLON(loc);}
true            {return JSON::JsonParser::make_JSON_TRUE(true, loc);}
false           {return JSON::JsonParser::make_JSON_FALSE(false, loc);}
null            {return JSON::JsonParser::make_JSON_NULL(loc);}
{STRING}        {
  size_t slen = strlen(yytext);
  return JSON::JsonParser::make_JSON_STRING(std::string(yytext+1, slen-2), loc);
  }
{INTNUM}        {  
  errno = 0;
  long n = strtol (yytext, NULL, 10);
  return JSON::JsonParser::make_JSON_INT(n, loc);  }
{FLOAT}         {
  double n = strtod (yytext, NULL);  
  return JSON::JsonParser::make_JSON_DOUBLE(n, loc);
}

{WHITESPACE}    {/*IGNORE*/}

%%


void
JSON::JsonDriver::prepare_string(const std::string data) {
  //yy_flex_debug = trace_scanning;
  yy_scan_string(data.c_str());
}