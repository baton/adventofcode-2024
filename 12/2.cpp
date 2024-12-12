#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <set>
#include <string>
#include <memory>
#include <iterator>


std::pair< int, int > constexpr directions[]{ { -1, 0 }, { 0, 1 }, { 1, 0 }, { 0, -1 } };


int main( int argc, char * argv[] )
{
	if( argc < 2 )
		return 0;

	std::ifstream ifs( argv[ 1 ] );

	std::vector< std::string > const tmap{ std::istream_iterator< std::string >( ifs ), std::istream_iterator< std::string >() };

	int const length{ static_cast< int >( tmap[ 0 ].size() ) };
	int const width{ static_cast< int >( tmap.size() ) };

	uint64_t price{ 0 };

	std::set< std::pair< int, int > > visited;
	for( int j{ 0 }; j != width; ++j )
		for( int i{ 0 }; i != length; ++i )
			if( !visited.count( { i, j } ) )
			{
				char const c{ tmap[ j ][ i ] };

				std::set< std::pair< int, int > > region;
				std::set< std::tuple< int, int, int, int > > border;

				std::list< std::pair< int, int > > front;
				front.emplace_back( i, j );

				while( !front.empty() )
				{
					auto const [ x, y ] = front.front();
					front.pop_front();

					auto const ii{ region.emplace( x, y ) };
					if( !ii.second )
						continue;

					for( auto const [ dx, dy ] : directions )
					{
						int const xx{ x + dx }, yy{ y + dy };
						if( region.count( { xx, yy } ) )
							continue;

						if( ( xx < 0 ) || ( xx == length )
							|| ( yy < 0 ) || ( yy == width )
							|| ( tmap[ yy ][ xx ] != c ) )
							border.emplace( xx, yy, dx, dy );
						else
							front.emplace_back( xx, yy );
					}
				}

				size_t sides{ 0 };

				while( !border.empty() )
				{
					++sides;
					auto [ x, y, u, v ] = *border.begin();
					int dx{ v }, dy{ -u };
					while( border.count( { x - dx, y - dy, u, v } ) )
					{
						x -= dx;
						y -= dy;
					}
					while( border.count( { x, y, u, v } ) )
					{
						border.erase( { x, y, u, v } );
						x += dx;
						y += dy;
					}
				}

				price += sides * region.size();

				visited.merge( std::move( region ) );
			}

	std::cout << "result = " << price << std::endl;

	return 0;
}