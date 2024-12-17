#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <set>
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

	std::map< std::tuple< int, int, int, int >, std::pair< size_t, std::set< std::pair< int, int > > > > data;
	std::list< std::tuple< int, int, int, int, size_t, std::set< std::pair< int, int > > > > front;

	std::set< std::pair< int, int > > init;
	init.emplace( 1, m.size() - 2 );
	front.emplace_back( 1, m.size() - 2, 1, 0, 0, init );

	std::map< size_t, std::set< std::pair< int, int > > > paths;

	while( !front.empty() )
	{
		auto [ x, y, dx, dy, q, p ] = front.front();
		front.pop_front();

		auto i{ data.find( { x, y, dx, dy } ) };
		if( ( i == data.end() ) || ( q < i->second.first ) )
			data[ { x, y, dx, dy } ] = { q, p };
		else if( q > i->second.first )
			continue;

		if( ( x == m[ 0 ].size() - 2 ) && ( y == 1 ) )
		{
			auto pi{ paths.find( q ) };
			if( pi != paths.end() )
				pi->second.merge( p );
			else
				paths.emplace( q, p );
				
			continue;
		}

		if( false )
		{
			std::vector< std::string > mm{ m };
			if( dx > 0 )
				mm[ y ][ x ] = '>';
			else if( dx < 0 )
				mm[ y ][ x ] = '<';
			else if( dy < 0 )
				mm[ y ][ x ] = '^';
			else
				mm[ y ][ x ] = 'v';
			for( auto const [ a, b ] : p )
				mm[ b ][ a ] = 'O';
			for( std::string const & s : mm )
				std::cout << s << std::endl;
			std::cout << std::endl;
		}

		if( dy == 0 )
		{
			front.emplace_back( x, y, 0, 1, q + 1000, p );
			front.emplace_back( x, y, 0, -1, q + 1000, p );
		}
		else
		{
			front.emplace_back( x, y, 1, 0, q + 1000, p );
			front.emplace_back( x, y, -1, 0, q + 1000, p );
		}

		if( m[ y + dy ][ x + dx ] != '#' )
		{
			p.emplace( x + dx, y + dy );
			front.emplace_back( x + dx, y + dy, dx, dy, q + 1, p );
		}
	}

	std::cout << "result = " << paths.begin()->second.size() << std::endl;

	return 0;
}