#ifndef _RAPID_PARSER_DESERIALIZER_XML_HPP_
#define _RAPID_PARSER_DESERIALIZER_XML_HPP_

#include "Deserializer.hpp"

#include <rapidxml/rapidxml.hpp>
#include <rapidxml/rapidxml_print.hpp>

#include <sstream>

namespace rapid_parser
{

class DeserializerXml : public Deserializer
{
public:
	DeserializerXml()
		: Deserializer()
	{
	}

	bool get( const char* key, std::string& data, const std::vector< std::pair< char*, size_t > >& path );
	bool get( const char* key, int& data,         const std::vector< std::pair< char*, size_t > >& path );
	bool get( const char* key, double& data,      const std::vector< std::pair< char*, size_t > >& path );
	bool get( const char* key, bool& data,        const std::vector< std::pair< char*, size_t > >& path );

	void load( const std::string& string );
	
private:
	rapidxml::xml_node<>* getValue( const std::vector< std::pair< char*, size_t > >& path );

private:
	rapidxml::xml_document<> doc;
};

}

#include "DeserializerXml.tcc"

#endif