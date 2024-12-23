#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <map>
#include <list>
#include <algorithm>


int main( int argc, char * argv[] )
{
	if( argc < 2 )
		return 0;

	std::ifstream ifs( argv[ 1 ] );

	std::map< std::string, std::set< std::string > > conns;
	std::list< std::set< std::string > > lans;

	for( std::string s; std::getline( ifs, s ); )
	{
		std::string const a{ s.substr( 0, 2 ) };
		std::string const b{ s.substr( 3 ) };

		conns[ a ].insert( b );
		conns[ b ].insert( a );

		lans.push_back( { a, b } );
	}

	for( std::list< std::set< std::string > > l; l != lans; )
	{
		l = lans;
		for( auto & x : lans )
			for( auto const & a : x )
				for( auto const & b : conns[ a ] )
				{
					size_t n{ 0 };
					for( auto const & c : conns[ b ] )
						if( x.count( c ) )
							++n;
					if( n == x.size() )
						x.insert( b );
				}
	}

	auto const m{ *std::max_element( lans.cbegin(), lans.cend(),
		[]( auto const & a, auto const & b ) -> bool { return a.size() < b.size(); } ) };

	std::string r;
	for( auto const & s : m )
	{
		if( !r.empty() )
			r += ",";
		r += s;
	}

	std::cout << "result = " << r << std::endl;

	return 0;
}