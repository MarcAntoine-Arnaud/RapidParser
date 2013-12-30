#ifndef _RAPID_PARSER_SERIALIZER_HPP_
#define _RAPID_PARSER_SERIALIZER_HPP_

#include <vector>

namespace rapid_parser
{

class Serializer
{
public:
	Serializer()
	{
	}
	
	virtual void add( const char* key, const std::string& data, const std::vector< char* >& path ) = 0;
	virtual void add( const char* key, const size_t data, const std::vector< char* >& path ) = 0;
	virtual void add( const char* key, const int data, const std::vector< char* >& path ) = 0;
	virtual void add( const char* key, const double data, const std::vector< char* >& path ) = 0;
	
	virtual void addEmptyElement( const std::vector< char* >& path ) = 0;
	
	virtual std::string get() = 0;
};

}
#endif
