#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <list>
#include <string>
#include <memory>


int main( int argc, char * argv[] )
{
	if( argc < 2 )
		return 0;

	std::ifstream ifs( argv[ 1 ] );

	std::set< std::pair< int, int > > blocks;
	int const w{ 71 };
	int const h{ 71 };

	size_t steps{ 1024 };
	for( std::string s; std::getline( ifs, s ) && steps; --steps )
	{
		int x{ 0 }, y{ 0 };
		std::sscanf( s.c_str(), "%i,%i", &x, &y );
		blocks.emplace( x, y );
	}

	std::list< std::tuple< int, int, int > > front;
	front.emplace_back( 0, 0, 0 );

	std::set< std::pair< int, int > > visited;

	int len{ w * h };

	while( !front.empty() )
	{
		auto const [ x, y, l ]{ front.front() };
		front.pop_front();

		if( blocks.count( { x, y } ) )
			continue;

		if( !visited.emplace( x, y ).second )
			continue;

		if( ( x == ( w - 1 ) ) && ( y == ( h - 1 ) ) )
		{
			if( l < len )
				len = l;

			continue;
		}

		if( x > 0 )
			front.emplace_back( x - 1, y, l + 1 );
		if( y > 0 )
			front.emplace_back( x, y - 1, l + 1 );
		if( x < ( w - 1 ) )
			front.emplace_back( x + 1, y, l + 1 );
		if( y < ( h - 1 ) )
			front.emplace_back( x, y + 1, l + 1 );
	}

	std::cout << "result = " << len << std::endl;

	return 0;
}