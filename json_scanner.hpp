#ifndef __MCSCANNER_HPP__
#define __MCSCANNER_HPP__ 1

#if ! defined(yyFlexLexerOnce)
#include <FlexLexer.h>
#endif

// # define YY_DECL \
//   JSON::JsonParser::symbol_type JSON::JsonScanner::yylex ()

#include "json_parser.tab.hh"


namespace JSON{

class JsonScanner : public yyFlexLexer{
public:
   

private:
   // /* hide this one from public view */
   //JsonParser::symbol_type yylex();
   // /* yyval ptr */
   // JSON::JsonParser::semantic_type *yylval;
};

} /* end namespace MC */

#endif /* END __MCSCANNER_HPP__ */
