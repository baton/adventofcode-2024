#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <list>
#include <string>
#include <memory>


int constexpr w{ 71 };
int constexpr h{ 71 };


bool go( std::set< std::pair< int, int > > const & blocks )
{
	std::list< std::pair< int, int > > front;
	front.emplace_back( 0, 0 );

	std::set< std::pair< int, int > > visited;
	bool found{ false };

	while( !front.empty() && !found )
	{
		auto const [ x, y ]{ front.front() };
		front.pop_front();

		if( blocks.count( { x, y } ) )
			continue;

		if( !visited.emplace( x, y ).second )
			continue;

		if( ( x == ( w - 1 ) ) && ( y == ( h - 1 ) ) )
		{
			found = true;

			continue;
		}

		if( x > 0 )
			front.emplace_back( x - 1, y );
		if( y > 0 )
			front.emplace_back( x, y - 1 );
		if( x < ( w - 1 ) )
			front.emplace_back( x + 1, y );
		if( y < ( h - 1 ) )
			front.emplace_back( x, y + 1 );
	}

	return found;
}

int main( int argc, char * argv[] )
{
	if( argc < 2 )
		return 0;

	std::ifstream ifs( argv[ 1 ] );

	std::set< std::pair< int, int > > blocks;

	for( std::string s; std::getline( ifs, s ); )
	{
		int x{ 0 }, y{ 0 };
		std::sscanf( s.c_str(), "%i,%i", &x, &y );
		blocks.emplace( x, y );

		if( !go( blocks ) )
		{
			std::cout << "result = " << x << "," << y << std::endl;

			break;
		}
	}

	return 0;
}