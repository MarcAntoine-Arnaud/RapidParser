
#include <cstring>

namespace rapid_parser
{

bool DeserializerXml::get( const char* key, std::string& data, const std::vector< std::pair< char*, size_t > >& path )
{
	rapidxml::xml_node<>* v = getValue( path );
	if( v == nullptr )
		return false;

	rapidxml::xml_node<>* n = v->first_node( key );
	if( n != nullptr )
	{
		data = n->value();
		return true;
	}
	return false;
}

bool DeserializerXml::get( const char* key, int& data, const std::vector< std::pair< char*, size_t > >& path )
{
	rapidxml::xml_node<>* v = getValue( path );
	if( v == nullptr )
		return false;

	rapidxml::xml_node<>* n = v->first_node( key );
	if( n != nullptr )
	{
		data = std::stoi( std::string( n->value() ) );
		return true;
	}
	return false;
}

bool DeserializerXml::get( const char* key, double& data, const std::vector< std::pair< char*, size_t > >& path )
{
	rapidxml::xml_node<>* v = getValue( path );
	if( v == nullptr )
		return false;

	rapidxml::xml_node<>* n = v->first_node( key );
	if( n != nullptr )
	{
		data = std::stod( std::string( n->value() ) );
		return true;
	}
	return false;
}

bool DeserializerXml::get( const char* key, bool& data, const std::vector< std::pair< char*, size_t > >& path )
{
	rapidxml::xml_node<>* v = getValue( path );
	if( v == nullptr )
		return false;

	rapidxml::xml_node<>* n = v->first_node( key );
	if( n != nullptr )
	{
		if( std::string( n->value() ) == "true" )
		{
			data = true;
			return true;
		}
		if( std::string( n->value() ) == "false" )
		{
			data = false;
			return true;
		}
	}
	return false;
}

void DeserializerXml::load( const std::string& string )
{
	doc.parse<0>( (char*) string.c_str() );
}

rapidxml::xml_node<>* DeserializerXml::getValue( const std::vector< std::pair< char*, size_t > >& path )
{
	rapidxml::xml_node<>* v = nullptr;
	if( path.size() )
	{
		for( std::pair< char*, size_t > p : path )
		{
			if( v == nullptr )
			{
				rapidxml::xml_node<>* n = doc.first_node( p.first );
				if( n != nullptr )
				{
					v = n;
				}
			}
			else
			{
				rapidxml::xml_node<>* n = v->first_node( p.first );
				if( n != nullptr )
				{
					for( size_t i = 0; i < p.second; i++ )
					{
						n = n->next_sibling();
					}
				}
				v = n;
			}
		}
	}
	return v;
}

	
}

