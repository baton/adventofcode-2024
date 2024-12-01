#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <numeric>


int main( int argc, char * argv[] )
{
	if( argc < 2 )
		return 0;

	std::ifstream ifs( argv[ 1 ] );

	std::vector< int64_t > a, b;
	while( !ifs.eof() )
	{
		int64_t x, y;
		ifs >> x >> y;
		a.push_back( x );
		b.push_back( y );
	}

	int64_t const result{
		std::transform_reduce(
			a.cbegin(), a.cend(),
			0LL,
			std::plus< int64_t >(),
			[ &b ]( int64_t const x ) -> int64_t
			{
				return x * std::count( b.cbegin(), b.cend(), x );
			}
		)
	};

	std::cout << "result = " << result << std::endl;

	return 0;
}