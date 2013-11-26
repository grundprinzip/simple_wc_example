#include <cctype>
#include <fstream>
#include <cassert>

#include "json_driver.hpp"
#include "json_st.hh"

JSON::JsonDriver::~JsonDriver(){ 
}

void 
JSON::JsonDriver::parse( const std::string& data )
{
   prepare_string(data);
   JSON::JsonParser parser (*this);
   parser.set_debug_level (trace_parsing);
   parser.parse ();
}


std::ostream& 
JSON::JsonDriver::print( std::ostream &stream )
{
   return stream;
}
