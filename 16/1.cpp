#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <list>
#include <string>
#include <memory>
#include <iterator>
#include <limits>


int main( int argc, char * argv[] )
{
	if( argc < 2 )
		return 0;

	std::ifstream ifs( argv[ 1 ] );

	std::vector< std::string > const m{ std::istream_iterator< std::string >( ifs ), std::istream_iterator< std::string >() };

	std::map< std::tuple< int, int, int, int >, size_t > data;
	std::list< std::tuple< int, int, int, int, size_t > > front;

	front.emplace_back( 1, m.size() - 2, 1, 0, 0 );
	while( !front.empty() )
	{
		auto [ x, y, dx, dy, q ] = front.front();
		front.pop_front();

		auto i{ data.find( { x, y, dx, dy } ) };
		if( ( i == data.end() ) || ( q < i->second ) )
			data[ { x, y, dx, dy } ] = q;
		else
			continue;

		if( m[ y + dy ][ x + dx ] != '#' )
			front.emplace_back( x + dx, y + dy, dx, dy, q + 1 );
		if( dy == 0 )
		{
			front.emplace_back( x, y, 0, 1, q + 1000 );
			front.emplace_back( x, y, 0, -1, q + 1000 );
		}
		else
		{
			front.emplace_back( x, y, 1, 0, q + 1000 );
			front.emplace_back( x, y, -1, 0, q + 1000 );
		}
	}

	size_t result{ std::numeric_limits< size_t >::max() };
	int dx{ 1 }, dy{ 0 };
	for( size_t d{ 0 }; d != 4; ++d )
	{
		auto i{ data.find( { m[ 0 ].size() - 2, 1, dx, dy } ) };
		if( ( i != data.end() ) && ( i->second < result ) )
			result = i->second;
		int t{ dy };
		dy = -dx;
		dx = t;
	}

	std::cout << "result = " << result << std::endl;

	return 0;
}