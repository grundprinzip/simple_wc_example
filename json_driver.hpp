#ifndef __MCDRIVER_HPP__
#define __MCDRIVER_HPP__ 1

#include <string>

#include "json_parser.tab.hh"

# define YY_DECL \
JSON::JsonParser::symbol_type yylex (JSON::JsonDriver& driver)
// ... and declare it for the parser's sake.
YY_DECL;

namespace JSON{

  class JsonDriver{
  public:
   JsonDriver(){};

   virtual ~JsonDriver();

   void prepare_string ( const std::string s);
   
   void parse( const std::string& data);


   void add_upper();
   void add_lower();
   void add_word( const std::string &word );
   void add_newline();
   void add_char();

   std::ostream& print(std::ostream &stream);
 private:

   bool trace_parsing = false;
   bool trace_scanning = false;

   int chars = 0;
   int words = 0;
   int lines = 0;
   int uppercase = 0;
   int lowercase = 0;   
 };

} /* end namespace MC */
#endif /* END __MCDRIVER_HPP__ */
