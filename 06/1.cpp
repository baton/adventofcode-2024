#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <string>
#include <iterator>
#include <algorithm>


int main( int argc, char * argv[] )
{
	if( argc < 2 )
		return 0;

	std::ifstream ifs( argv[ 1 ] );

	std::vector< std::string > const field{ std::istream_iterator< std::string >( ifs ), std::istream_iterator< std::string >() };

	int x{ 0 }, y{ 0 };
	auto i{ std::find_if( field.begin(), field.end(),
		[ &x ]( std::string const & s ) -> bool
		{
			size_t const p{ s.find( '^' ) };
			if( p != std::string::npos )
			{
				x = p;

				return true;
			}

			return false;
		} )
	};
	y = std::distance( field.begin(), i );

	std::set< std::pair< int, int > > visited;
	visited.emplace( x, y );

	int dx{ 0 }, dy{ -1 };
	while( ( ( y + dy ) >= 0 ) && ( ( y + dy ) < field.size() ) && ( ( x + dx ) >= 0 ) && ( ( x + dx ) < field[ y ].size() ) )
	{
		if( field[ y + dy ][ x + dx ] == '#' )
		{
			int const t{ dx };
			dx = -dy;
			dy = t;
		}
		else
		{
			x += dx;
			y += dy;

			visited.emplace( x, y );
		}
	}

	std::cout << "result = " << visited.size() << std::endl;

	return 0;
}