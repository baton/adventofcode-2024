#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <set>
#include <string>
#include <memory>
#include <iterator>


int main( int argc, char * argv[] )
{
	if( argc < 2 )
		return 0;

	std::ifstream ifs( argv[ 1 ] );

	std::vector< std::string > const tmap{ std::istream_iterator< std::string >( ifs ), std::istream_iterator< std::string >() };

	uint64_t sum{ 0 };

	for( size_t y{ 0 }; y != tmap.size(); ++y )
		for( size_t x{ 0 }; x != tmap[ y ].size(); ++x )
			if( tmap[ y ][ x ] == '0' )
			{
				std::set< std::pair< size_t, size_t > > ends;
				std::list< std::pair< size_t, size_t > > front;
				front.emplace_back( x, y );
				while( !front.empty() )
				{
					auto const [ x, y ] = front.front();
					front.pop_front();

					if( tmap[ y ][ x ] == '9' )
					{
						ends.emplace( x, y );

						continue;
					}

					if( ( x > 0 ) && ( tmap[ y ][ x - 1 ] == ( tmap[ y ][ x ] + 1 ) ) )
						front.emplace_back( x - 1, y );
					if( ( x < ( tmap[ y ].size() - 1 ) ) && ( tmap[ y ][ x + 1 ] == ( tmap[ y ][ x ] + 1 ) ) )
						front.emplace_back( x + 1, y );
					if( ( y > 0 ) && ( tmap[ y - 1 ][ x ] == ( tmap[ y ][ x ] + 1 ) ) )
						front.emplace_back( x, y - 1 );
					if( ( y < ( tmap.size() - 1 ) ) && ( tmap[ y + 1 ][ x ] == ( tmap[ y ][ x ] + 1 ) ) )
						front.emplace_back( x, y + 1 );
				}

				sum += ends.size();
			}

	std::cout << "result = " << sum << std::endl;

	return 0;
}