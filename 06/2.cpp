#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <tuple>
#include <string>
#include <iterator>
#include <algorithm>


int main( int argc, char * argv[] )
{
	if( argc < 2 )
		return 0;

	std::ifstream ifs( argv[ 1 ] );

	std::vector< std::string > const field{ std::istream_iterator< std::string >( ifs ), std::istream_iterator< std::string >() };

	int x0{ 0 }, y0{ 0 };
	auto i{ std::find_if( field.begin(), field.end(),
		[ &x0 ]( std::string const & s ) -> bool
		{
			size_t const p{ s.find( '^' ) };
			if( p != std::string::npos )
			{
				x0 = p;

				return true;
			}

			return false;
		} )
	};
	y0 = std::distance( field.begin(), i );

	std::set< std::pair< int, int > > visited;

	{
		int x{ x0 }, y{ y0 }, dx{ 0 }, dy{ -1 };
		visited.emplace( x, y );

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
	}

	visited.erase( { x0, y0 } );
	size_t count{ 0 };

	for( auto const & [ tx, ty ] : visited )
	{
		std::vector< std::string > f{ field };
		f[ ty ][ tx ] = '#';

		int x{ x0 }, y{ y0 }, dx{ 0 }, dy{ -1 };
		std::set< std::tuple< int, int, int, int > > vd;
		vd.emplace( x, y, dx, dy );

		while( ( ( y + dy ) >= 0 ) && ( ( y + dy ) < f.size() ) && ( ( x + dx ) >= 0 ) && ( ( x + dx ) < f[ y ].size() ) )
		{
			if( f[ y + dy ][ x + dx ] == '#' )
			{
				int const t{ dx };
				dx = -dy;
				dy = t;
			}
			else
			{
				x += dx;
				y += dy;

				auto c{ vd.emplace( x, y, dx, dy ) };
				if( !c.second )
				{
					++count;

					break;
				}
			}
		}

	}

	std::cout << "result = " << count << std::endl;

	return 0;
}