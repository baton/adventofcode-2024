#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>


int main( int argc, char * argv[] )
{
	if( argc < 2 )
		return 0;

	uint64_t sum{ 0 };

	std::ifstream ifs( argv[ 1 ] );
	for( std::string s; std::getline( ifs, s ); )
	{
		char * e{ nullptr };
		uint64_t const val{ std::strtoull( s.data(), &e, 10 ) };

		std::vector< uint64_t > v;

		std::istringstream iss( e + 2 );
		while( !iss.eof() )
		{
			uint64_t x{ 0 };
			iss >> x;

			if( v.empty() )
			{
				v.push_back( x );

				continue;
			}

			std::vector< uint64_t > vv;
			for( uint64_t const a : v )
			{
				vv.emplace_back( a + x );
				vv.emplace_back( a * x );
			}

			v = std::move( vv );
		}

		if( std::find( v.cbegin(), v.cend(), val ) != v.cend() )
			sum += val;
	}

	std::cout << "result = " << sum << std::endl;

	return 0;
}
