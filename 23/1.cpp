#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <map>


int main( int argc, char * argv[] )
{
	if( argc < 2 )
		return 0;

	std::ifstream ifs( argv[ 1 ] );

	std::map< std::string, std::set< std::string > > conns;

	for( std::string s; std::getline( ifs, s ); )
	{
		std::string const a{ s.substr( 0, 2 ) };
		std::string const b{ s.substr( 3 ) };

		conns[ a ].insert( b );
		conns[ b ].insert( a );
	}

	std::set< std::set< std::string > > tri;

	for( auto const & [ a, l ] : conns )
		if( a[ 0 ] == 't' )
			for( auto const & b : l )
				for( auto const & c : conns[ b ] )
					if( ( a != c ) && conns[ c ].count( a ) )
						tri.insert( { a, b, c } );

	std::cout << "result = " << tri.size() << std::endl;

	return 0;
}