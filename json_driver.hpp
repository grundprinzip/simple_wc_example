#ifndef __MCDRIVER_HPP__
#define __MCDRIVER_HPP__ 1

#include <string>
#include <iostream>

#include "json_parser.tab.hh"
#include "json_st.hh"

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

   std::ostream& print(std::ostream &stream);


   void log(){
      #ifndef NDEBUG
      std::cout << std::endl;
      #endif
   }

   template<typename T, typename... R>
   void log(T v, R...r) {
      #ifndef NDEBUG
      std::cout << v;
      #endif
      log(r...);
   }


   // Result json value
   Value result;

 private:

   bool trace_parsing = false;
   bool trace_scanning = false;
 };

} /* end namespace MC */
#endif /* END __MCDRIVER_HPP__ */
