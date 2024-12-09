#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <set>
#include <memory>


int main( int argc, char * argv[] )
{
	if( argc < 2 )
		return 0;

	int x_max{ 0 }, y_max{ 0 };
	std::set< std::pair< int, int > > all_nodes;
	std::map< char, std::set< std::pair< int, int > > > nodes;

	std::ifstream ifs( argv[ 1 ] );
	for( std::string s; std::getline( ifs, s ); )
	{
		x_max = s.size();
		for( int x{ 0 }; x != s.size(); ++x )
			if( s[ x ] != '.' )
			{
				nodes[ s[ x ] ].emplace( x, y_max );
				all_nodes.emplace( x, y_max );
			}

		++y_max;
	}

	std::set< std::pair< int, int > > antinodes;

	for( auto const & [ f, ns ] : nodes )
		for( auto const & a : ns )
			for( auto const & b : ns )
				if( a != b )
				{
					std::pair< int, int > const an{ 2 * b.first - a.first, 2 * b.second - a.second };

					if( an.first < 0 )
						continue;
					if( an.second < 0 )
						continue;
					if( an.first >= x_max )
						continue;
					if( an.second >= y_max )
						continue;

					antinodes.insert( an );
				}

	std::cout << "result = " << antinodes.size() << std::endl;

	return 0;
}