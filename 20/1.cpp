#include <iostream>
#include <fstream>
#include <map>
#include <memory>
#include <string>


int main( int argc, char * argv[] )
{
	if( argc < 2 )
		return 0;

	std::ifstream ifs( argv[ 1 ] );

	std::map< std::pair< int, int >, size_t > path;
	std::pair< int, int > s, e;

	int y{ 0 };
	for( std::string t; std::getline( ifs, t ); )
	{
		for( int x{ 0 }; x != t.size(); ++x )
			switch( t[ x ] )
			{
				case 'E':
					e = { x, y };
				case '.':
					path[ { x, y } ] = -1;
					break;
				case 'S':
					s = { x, y };
					path[ { x, y } ] = 0;
					break;
				default:
					break;
			}
		++y;
	}

	size_t l{ 0 };
	for( std::pair< int, int > p{ s }; p != e; ++l )
	{
		path[ p ] = l;
		auto const [ x, y ] = p;
		for( auto const [ u, v ] : { std::pair{ -1, 0 }, { 0, 1 }, { 1, 0 }, { 0, -1 } } )
		{
			p = { x + u, y + v };
			auto i{ path.find( p ) };
			if( ( i != path.end() ) && ( i->second == -1 ) )
				break;
		}
	}
	path[ e ] = l;

	size_t count{ 0 };

	for( auto const [ p, l ] : path )
	{
		auto const [ x, y ] = p;
		for( auto const [ u, v ] : { std::pair{ -2, 0 }, { 0, 2 }, { 2, 0 }, { 0, -2 } } )
		{
			auto i{ path.find( { x + u, y + v } ) };
			if( ( i != path.end() ) && ( i->second >= ( l + 2 + 100 ) ) )
				++count;
		}
	}

	std::cout << "result = " << count << std::endl;

	return 0;
}