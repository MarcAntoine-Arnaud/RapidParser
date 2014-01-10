#ifndef _RAPID_PARSER_DESERIALIZER_JSON_HPP_
#define _RAPID_PARSER_DESERIALIZER_JSON_HPP_

#include "Deserializer.hpp"

#include <rapidjson/rapidjson.h>
#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>
#include <rapidjson/prettywriter.h>

namespace rapid_parser
{

class DeserializerJson : public Deserializer
{
public:
	DeserializerJson()
		: Deserializer()
	{
	}

	bool get( const char* key, std::string& data, const std::vector< std::pair< char*, size_t > >& path );
	bool get( const char* key, int&         data, const std::vector< std::pair< char*, size_t > >& path );
	bool get( const char* key, double&      data, const std::vector< std::pair< char*, size_t > >& path );
	bool get( const char* key, bool&        data, const std::vector< std::pair< char*, size_t > >& path );

	void load( const std::string& string );
	
private:
	rapidjson::Value* getValue( const std::vector< std::pair< char*, size_t > >& pat);
	std::string valueToString( const rapidjson::Value* value );

private:
	rapidjson::Document doc;
};

}

#include "DeserializerJson.tcc"

#endif