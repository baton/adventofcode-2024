#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>


int64_t signum( int64_t const x )
{
	return x < 0 ? -1 : ( x > 0 ? 1 : 0 );
}


int main( int argc, char * argv[] )
{
	if( argc < 2 )
		return 0;

	std::ifstream ifs( argv[ 1 ] );

	uint64_t count{ 0 };
	while( !ifs.eof() )
	{
		std::string s;
		std::getline( ifs, s );

		std::istringstream iss( s );
		int sign{ 0 };
		bool good{ true };
		int64_t x{ 0 };
		iss >> x;
		while( !iss.eof() )
		{
			int64_t y;
			iss >> y;

			int64_t const d{ y - x };
			x = y;

			if( ( std::abs( d ) < 1 ) || ( std::abs( d ) > 3 ) )
			{
				good = false;

				break;
			}

			int64_t const sd{ signum( d ) };
			if( sign == 0 )
			{
				sign = sd;

				continue;
			}

			if( sign != sd )
			{
				good = false;

				break;
			}
		}	

		if( good )
			++count;
	}

	std::cout << "result = " << count << std::endl;

	return 0;
}