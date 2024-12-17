#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <set>
#include <string>
#include <memory>


std::pair< int, int > dir( char const c )
{
	switch( c )
	{
		case '^': return {  0, -1 };
		case '>': return {  1,  0 };
		case 'v': return {  0,  1 };
		case '<': return { -1,  0 };

		default: return {};
	}
}


int main( int argc, char * argv[] )
{
	if( argc < 2 )
		return 0;

	std::ifstream ifs( argv[ 1 ] );

	std::vector< std::string > m;

	for( std::string s; std::getline( ifs, s ) && !s.empty(); )
		m.push_back( s );

	int const w{ static_cast< int >( m[ 0 ].size() ) };
	int const h{ static_cast< int >( m.size() ) };

	bool found{ false };
	size_t x{ 0 }, y{ 0 };
	for( ; x != w; ++x )
	{
		for( y = 0; y != h; ++y )
			if( found = ( m[ y ][ x ] == '@' ) )
				break;
		if( found )
			break;
	}

	for( std::string s; std::getline( ifs, s ); )
		for( char const c : s )
		{
			auto const [ dx, dy ]{ dir( c ) };
			int l{ 1 };
			while( m[ y + dy * l ][ x + dx * l ] == 'O' )
				++l;
			if( m[ y + dy * l ][ x + dx * l ] == '.' )
			{
				while( l != 0 )
				{
					m[ y + dy * l ][ x + dx * l ] = 'O';
					--l;
				}
				m[ y + dy ][ x + dx ] = '@';
				m[ y ][ x ] = '.';

				x += dx;
				y += dy;
			}
		}

	uint64_t sum{ 0 };
	for( size_t j{ 0 }; j != m.size(); ++j )
		for( size_t i{ 0 }; i != m[ j ].size(); ++i )
			if( m[ j ][ i ] == 'O' )
				sum += j * 100 + i;

	std::cout << "result = " << sum << std::endl;

	return 0;
}