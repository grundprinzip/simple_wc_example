#include <cctype>
#include <fstream>
#include <cassert>

#include "json_driver.hpp"

JSON::MC_Driver::~MC_Driver(){ 
   delete(scanner);
   scanner = nullptr;
   delete(parser);
   parser = nullptr;
}

void 
JSON::MC_Driver::parse( const char *filename )
{
   assert( filename != nullptr );
   std::ifstream in_file( filename );
   if( ! in_file.good() ) exit( EXIT_FAILURE );
   
   delete(scanner);
   try
   {
      scanner = new JSON::MC_Scanner( &in_file );
   }
   catch( std::bad_alloc &ba )
   {
      std::cerr << "Failed to allocate scanner: (" <<
         ba.what() << "), exiting!!\n";
      exit( EXIT_FAILURE );
   }
   
   delete(parser); 
   try
   {
      parser = new JSON::MC_Parser( (*scanner) /* scanner */, 
                                  (*this) /* driver */ );
   }
   catch( std::bad_alloc &ba )
   {
      std::cerr << "Failed to allocate parser: (" << 
         ba.what() << "), exiting!!\n";
      exit( EXIT_FAILURE );
   }
   const int accept( 0 );
   if( parser->parse() != accept )
   {
      std::cerr << "Parse failed!!\n";
   }
}

void 
JSON::MC_Driver::add_upper()
{ 
   uppercase++; 
   chars++; 
   words++; 
}

void 
JSON::MC_Driver::add_lower()
{ 
   lowercase++; 
   chars++; 
   words++; 
}

void 
JSON::MC_Driver::add_word( const std::string &word )
{
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
JSON::MC_Driver::add_newline()
{ 
   lines++; 
   chars++; 
}

void 
JSON::MC_Driver::add_char()
{ 
   chars++; 
}


std::ostream& 
JSON::MC_Driver::print( std::ostream &stream )
{
   stream << "Uppercase: " << uppercase << "\n";
   stream << "Lowercase: " << lowercase << "\n";
   stream << "Lines: " << lines << "\n";
   stream << "Words: " << words << "\n";
   stream << "Characters: " << chars << "\n";
   return(stream);
}
