#include <iostream>
#include <cstdlib>

#include "json_driver.hpp"

int 
main(const int argc, const char **argv)
{
   if(argc != 2 ) 
      return ( EXIT_FAILURE );
   

   JSON::JsonDriver driver;
   
   std::string tt = "Hallow Welt";
   driver.parse( tt );
   
   std::cout << "Results\n";
   
   driver.print(std::cout) << "\n";

   return( EXIT_SUCCESS );
}
