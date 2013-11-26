#include <iostream>
#include <cstdlib>

#include "json_driver.hpp"

int 
main(const int argc, const char **argv)
{
   if(argc != 2 ) 
      return ( EXIT_FAILURE );
   
   std::string data = "{  \"priority\" : 1,   \"performance\": false,   \"operators\": {    \"0\": {       \"type\": \"NoOp\"     }   },  \"edges\": [[\"0\", \"0\"]]}";
   JSON::JsonDriver driver;
   
   size_t s = 0;
   for(size_t i=0; i < 100000; ++i) {
     driver.parse( data );
     s += driver.result["edges"].size();     
   }
   std::cout << s << std::endl;
   return s;
}
