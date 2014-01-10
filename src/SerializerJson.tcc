
#include <iostream>

namespace rapid_parser
{

rapidjson::Value* SerializerJson::getValue( const std::vector< char* >& path )
{
	rapidjson::Value* v = nullptr;
	if( path.size() )
	{
		for( auto p : path )
		{
			v = get( p, v );
		}
	}
	return v;
}

rapidjson::Value* SerializerJson::get( const char* id, rapidjson::Value* ref )
{
	using namespace rapidjson;
	if( ref == nullptr )
	{
		if( doc.HasMember( id ) )
		{
			return &doc[ id ][0u];
		}
		else
		{
			Value array( kArrayType );
			Value firstChild( kObjectType );
			doc.AddMember( id, array, doc.GetAllocator() );
			doc[ id ].PushBack( firstChild, doc.GetAllocator() );
			return &doc[ id ][0u];
		}
	}
	else
	{
		if( ref->HasMember( id ) )
		{
			return &ref[0u][id][ ref[0u][ id ].Size() - 1 ];
		}
		else
		{
			Value array( kArrayType );
			Value newChild( kObjectType );
			ref[0u].AddMember( id, array, doc.GetAllocator() );
			ref[0u][ id ].PushBack( newChild, doc.GetAllocator() );
			return &ref[0u][ id ][0u];
		}
	}
	return nullptr;
}

void SerializerJson::add( const char* key, rapidjson::Value& value, const std::vector< char* >& path )
{
	rapidjson::Value* v = getValue( path );
	
	if( v == nullptr )
		doc.AddMember( key, doc.GetAllocator(), value, doc.GetAllocator() );
	else
		v->AddMember( key, doc.GetAllocator(), value, doc.GetAllocator() );
}

void SerializerJson::add( const char* key, const std::string& data, const std::vector< char* >& path )
{
	rapidjson::Value value( data.c_str(), data.size() );
	add( key, value, path );
}

void SerializerJson::add( const char* key, const size_t data, const std::vector< char* >& path )
{
	rapidjson::Value value( data );
	add( key, value, path );
}

void SerializerJson::add( const char* key, const int data, const std::vector< char* >& path )
{
	rapidjson::Value value( data );
	add( key, value, path );
}

void SerializerJson::add( const char* key, const double data, const std::vector< char* >& path )
{
	rapidjson::Value value( data );
	add( key, value, path );
}

void SerializerJson::add( const char* key, const bool data, const std::vector< char* >& path )
{
	rapidjson::Value value( data );
	add( key, value, path );
}

bool SerializerJson::pathExist( const std::vector< char* >& path )
{
	rapidjson::Value* v = &doc;
	if( path.size() )
	{
		for( auto p : path )
		{
			if( ! v->HasMember( p ) )
			{
				return false;
			}
			v = get( p, v );
		}
	}
	return true;
}

void SerializerJson::addEmptyElement( const std::vector< char* >& path )
{
	using namespace rapidjson;
	if( ! pathExist( path ) )
	{
		// create new path
		Value* v = getValue( path );
		return;
	}

	// create new element
	std::vector<char*> p;
	for( size_t index =0; index < path.size() - 1 ; ++index )
		p.push_back( path.at( index ) );
	
	Value* v = getValue( p );
	Value newChild( kObjectType );

	(*v)[ path.at( path.size() - 1 ) ].PushBack( newChild, doc.GetAllocator() );	
}

}
