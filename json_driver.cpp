#include <cctype>
#include <fstream>
#include <cassert>

#include "json_driver.hpp"

JSON::JsonDriver::~JsonDriver(){ 
}

void 
JSON::JsonDriver::parse( const std::string& data )
{
   std::cout <<data << std::endl;
   prepare_string(data);
   JSON::JsonParser parser (*this);
   parser.set_debug_level (trace_parsing);
   parser.parse ();
}

void 
JSON::JsonDriver::add_upper()
{ 
   uppercase++; 
   chars++; 
   words++; 
}

void 
JSON::JsonDriver::add_lower()
{ 
   lowercase++; 
   chars++; 
   words++; 
}

void 
JSON::JsonDriver::add_word( const std::string &word )
{
   std::cout << word << std::endl;
   words++; 
   chars += word.length();
   for(const char &c : word ){
      if( islower( c ) )
      { 
         lowercase++; 
      }
      else if ( isupper( c ) ) 
      { 
         uppercase++; 
      }
   }
}

void 
JSON::JsonDriver::add_newline()
{ 
   lines++; 
   chars++; 
}

void 
JSON::JsonDriver::add_char()
{ 
   chars++; 
}


std::ostream& 
JSON::JsonDriver::print( std::ostream &stream )
{
   stream << "Uppercase: " << uppercase << "\n";
   stream << "Lowercase: " << lowercase << "\n";
   stream << "Lines: " << lines << "\n";
   stream << "Words: " << words << "\n";
   stream << "Characters: " << chars << "\n";
   return(stream);
}
