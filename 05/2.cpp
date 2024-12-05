#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <set>
#include <string>


int main( int argc, char * argv[] )
{
	if( argc < 2 )
		return 0;

	std::ifstream ifs( argv[ 1 ] );

	std::map< int, std::set< int > > rules;
	std::map< int, std::set< int > > rules_b;

	while( !ifs.eof() )
	{
		std::string s;
		std::getline( ifs, s );
		if( s.empty() )
			break;

		int a{}, b{};
		std::sscanf( s.c_str(), "%i|%i", &a, &b );
		rules[ a ].insert( b );
		rules_b[ b ].insert( a );
	}

	int sum{ 0 };

	while( !ifs.eof() )
	{
		std::string s;
		std::getline( ifs, s );

		std::vector< int > v;

		std::istringstream iss( s );
		for( char a[ 4 ]{}; iss.getline( a, sizeof( a ), ',' ); )
			v.push_back( std::atoi( a ) );

		bool good{ true };
		for( size_t i{ 0 }; ( i != v.size() ) && good; ++i )
		{
			auto r{ rules.find( v[ i ] ) };
			if( r != rules.end() )
				for( size_t j{ 0 }; ( j != i ) && good; ++j )
					good &= r->second.count( v[ j ] ) == 0;
		}

		std::vector< int > g;
		if( !good )
		{
			for( int const x : v )
			{
				auto i{ g.begin() };

				auto rb{ rules_b.find( x ) };
				if( rb != rules_b.end() )
					for( auto j{ g.begin() }; j != g.end(); ++j )
						if( rb->second.count( *j ) != 0 )
							i = std::next( j );

				auto r{ rules.find( x ) };
				if( r != rules.end() )
					for( ; i != g.end(); ++i )
						if( r->second.count( *i ) != 0 )
							break;

				g.insert( i, x );
			}

			sum += g[ g.size() / 2 ];
		}
	}

	std::cout << "result = " << sum << std::endl;

	return 0;
}