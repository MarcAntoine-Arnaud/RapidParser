#ifndef _RAPID_PARSER_SERIALIZER_JSON_HPP_
#define _RAPID_PARSER_SERIALIZER_JSON_HPP_

#include "Serializer.hpp"

#include <rapidjson/rapidjson.h>
#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>
#include <rapidjson/prettywriter.h>

namespace rapid_parser
{

class SerializerJson : public Serializer
{
public:
	SerializerJson()
		: Serializer()
	{
		doc.SetObject();
	}

	void add( const char* key, const std::string& data, const std::vector< char* >& path );
	void add( const char* key, const size_t data, const std::vector< char* >& path );
	void add( const char* key, const int data, const std::vector< char* >& path );
	void add( const char* key, const double data, const std::vector< char* >& path );
	void add( const char* key, const bool data, const std::vector< char* >& path );
	
	void addEmptyElement( const std::vector< char* >& path );
	
	std::string get()
	{
		using namespace rapidjson;
		StringBuffer strbuf;

		if( indentOutput )
		{
			PrettyWriter< StringBuffer > writer( strbuf );
			doc.Accept( writer );
		}
		else
		{
			Writer< StringBuffer > writer( strbuf );
			doc.Accept( writer );
		}
		return strbuf.GetString();
	}
	
private:
	rapidjson::Value* getValue( const std::vector< char* >& path );
	rapidjson::Value* get( const char* id, rapidjson::Value* ref = nullptr );
	
	bool pathExist( const std::vector< char* >& path );

private:
	rapidjson::Document doc;
};

}

#include "SerializerJson.tcc"

#endif
