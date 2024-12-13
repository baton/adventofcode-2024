#include <iostream>
#include <fstream>
#include <string>
#include <limits>


int main( int argc, char * argv[] )
{
	if( argc < 2 )
		return 0;

	std::ifstream ifs( argv[ 1 ] );

	int64_t total_price{ 0 };

	while( !ifs.eof() )
	{
		std::string sa, sb, sp, t;
		std::getline( ifs, sa );
		std::getline( ifs, sb );
		std::getline( ifs, sp );
		std::getline( ifs, t );

		int64_t ax{ 0 }, ay{ 0 }, bx{ 0 }, by{ 0 }, px{ 0 }, py{ 0 };
		std::sscanf( sa.c_str(), "Button A: X+%lli, Y+%lli", &ax, &ay );
		std::sscanf( sb.c_str(), "Button B: X+%lli, Y+%lli", &bx, &by );
		std::sscanf( sp.c_str(), "Prize: X=%lli, Y=%lli", &px, &py );

		px += 10000000000000;
		py += 10000000000000;

		int64_t const d{ ax * by - bx * ay };
		if( d == 0 )
			continue;

		int64_t const da{ px * by - bx * py };
		int64_t const db{ ax * py - px * ay };

		if( ( ( da % d ) != 0 ) || ( ( db % d ) != 0 ) )
			continue;

		total_price += ( da / d ) * 3 + db / d;
	}

	std::cout << "result = " << total_price << std::endl;

	return 0;
}