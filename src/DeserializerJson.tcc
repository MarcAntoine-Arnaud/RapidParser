	
#include <stdexcept>

namespace rapid_parser
{

bool DeserializerJson::get( const char* key, std::string& data, const std::vector< std::pair< char*, size_t > >& path )
{
	rapidjson::Value* node = getValue( path );
	if( node == nullptr )
		return false;

	if( node->IsObject() && node->HasMember( key ) )
	{
		rapidjson::Value* value = &node->FindMember( key )->value;
		data = valueToString( value );
		return true;
	}
	return false;
}

bool DeserializerJson::get( const char* key, int& data, const std::vector< std::pair< char*, size_t > >& path )
{
	rapidjson::Value* node = getValue( path );
	if( node == nullptr )
		return false;

	if( node->IsObject() && node->HasMember( key ) )
	{
		rapidjson::Value* value = &node->FindMember( key )->value;
		if( value->IsInt() )
		{
			data = value->GetInt();
			return true;
		}
	}
	return false;
}

bool DeserializerJson::get( const char* key, double& data, const std::vector< std::pair< char*, size_t > >& path )
{
	rapidjson::Value* node = getValue( path );
	if( node == nullptr )
		return false;

	if( node->IsObject() && node->HasMember( key ) )
	{
		rapidjson::Value* value = &node->FindMember( key )->value;
		if( value->IsDouble() )
		{
			data = value->GetDouble();
			return true;
		}
	}
	return false;
}

bool DeserializerJson::get( const char* key, bool& data, const std::vector< std::pair< char*, size_t > >& path )
{
	rapidjson::Value* node = getValue( path );
	if( node == nullptr )
		return false;

	if( node->IsObject() && node->HasMember( key ) )
	{
		rapidjson::Value* value = &node->FindMember( key )->value;
		if( value->IsBool() )
		{
			data = value->GetBool();
			return true;
		}
	}
	return false;
}

void DeserializerJson::load( const std::string& string )
{
	doc.Parse<0>( string.c_str() );
	if( doc.HasParseError() )
		throw std::runtime_error( std::string( doc.GetParseError() ) + "  @char:# " + std::to_string( doc.GetErrorOffset() ) );
}

rapidjson::Value* DeserializerJson::getValue( const std::vector< std::pair< char*, size_t > >& path )
{
	rapidjson::Value* v = nullptr;
	if( path.size() )
	{
		for( std::pair< char*, size_t > p : path )
		{
			if( v == nullptr )
			{
				if( doc.HasMember( p.first ) )
					v = &doc[ p.first ][ p.second ];
			}
			else
			{
				if( v->HasMember( p.first ) )
				{
					rapidjson::Value::Member* member = v->FindMember( p.first );
					if( member->value.IsArray() )
					{
						v = &member->value[ p.second ];
					}
					else
					{
						v = &member->value;
					}
				}
				else
				{
					v = nullptr;
				}
			}
		}
	}
	return v;
}

std::string DeserializerJson::valueToString( const rapidjson::Value* value )
{
	std::string ret;
	if( value->IsInt() )
		ret = std::to_string( value->GetInt() );

	if( value->IsDouble() )
		ret = std::to_string( value->GetDouble() );

	if( value->IsString() )
		ret = value->GetString();
	return ret;
}

}
