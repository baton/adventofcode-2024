#include <iostream>
#include <fstream>
#include <string>


int main( int argc, char * argv[] )
{
	if( argc < 2 )
		return 0;

	std::ifstream ifs( argv[ 1 ] );

	size_t sum{ 0 };

	for( std::string s; std::getline( ifs, s ); )
	{
		size_t x{ std::stoull( s ) };
		for( size_t i{ 0 }; i != 2000; ++i )
		{
			x = ( x ^ ( x << 6 ) ) & 0xFFFFFFULL;
			x = ( x ^ ( x >> 5 ) ) & 0xFFFFFFULL;
			x = ( x ^ ( x << 11 ) ) & 0xFFFFFFULL;
		}

		sum += x;
	}

	std::cout << "result = " << sum << std::endl;

	return 0;
}
