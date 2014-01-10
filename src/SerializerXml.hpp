#ifndef _RAPID_PARSER_SERIALIZER_XML_HPP_
#define _RAPID_PARSER_SERIALIZER_XML_HPP_

#include "Serializer.hpp"

#include <rapidxml/rapidxml.hpp>
#include <rapidxml/rapidxml_print.hpp>

#include <sstream>

namespace rapid_parser
{

class SerializerXml : public Serializer
{
public:
	SerializerXml()
		: Serializer()
	{
		rapidxml::xml_node<> *decl = doc.allocate_node(rapidxml::node_declaration);
		decl->append_attribute( doc.allocate_attribute("version","1.0") );
		decl->append_attribute( doc.allocate_attribute("encoding","utf-8") );
		doc.append_node(decl);
	}
	
	void add( const char* key, const std::string& data, const std::vector< char* >& path );
	void add( const char* key, const size_t data,       const std::vector< char* >& path );
	void add( const char* key, const int data,          const std::vector< char* >& path );
	void add( const char* key, const double data,       const std::vector< char* >& path );
	void add( const char* key, const bool data,         const std::vector< char* >& path );
	
	void addEmptyElement( const std::vector< char* >& path );
	
	std::string get()
	{
		std::string stringDoc;
		rapidxml::print( std::back_inserter( stringDoc ), doc, ( ! indentOutput ) && rapidxml::print_no_indenting );
		return stringDoc;
	}

private:
	
	rapidxml::xml_node<>* getValue( const std::vector< char* >& path );
	rapidxml::xml_node<>* get( const char* id, rapidxml::xml_node<>* ref = nullptr );
	
private:
	rapidxml::xml_document<> doc;
};

}

#include "SerializerXml.tcc"

#endif
