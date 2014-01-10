#ifndef _RAPID_PARSER_DESERIALIZER_HPP_
#define _RAPID_PARSER_DESERIALIZER_HPP_

#include <vector>

namespace rapid_parser
{

class Deserializer
{
public:
	Deserializer()
	{
	}
	
	// virtual void get( const char* key, const std::string& data, const std::vector< char* >& path ) = 0;
	// virtual void get( const char* key, const size_t data, const std::vector< char* >& path ) = 0;
	// virtual void get( const char* key, const int data, const std::vector< char* >& path ) = 0;
	// virtual void get( const char* key, const double data, const std::vector< char* >& path ) = 0;
	
	virtual bool get( const char* key, std::string& data, const std::vector< std::pair< char*, size_t > >& path ) = 0;
	virtual bool get( const char* key, int& data,         const std::vector< std::pair< char*, size_t > >& path ) = 0;
	virtual bool get( const char* key, double& data,      const std::vector< std::pair< char*, size_t > >& path ) = 0;
	virtual bool get( const char* key, bool& data,        const std::vector< std::pair< char*, size_t > >& path ) = 0;

	virtual void load( const std::string& string ) = 0;

	// virtual std::string get() = 0;
};

}
#endif
