#include <iostream>
#include <fstream>
#include <string>
#include <limits>


int main( int argc, char * argv[] )
{
	if( argc < 2 )
		return 0;

	std::ifstream ifs( argv[ 1 ] );

	int total_price{ 0 };

	while( !ifs.eof() )
	{
		std::string sa, sb, sp, t;
		std::getline( ifs, sa );
		std::getline( ifs, sb );
		std::getline( ifs, sp );
		std::getline( ifs, t );

		int ax{ 0 }, ay{ 0 }, bx{ 0 }, by{ 0 }, px{ 0 }, py{ 0 };
		std::sscanf( sa.c_str(), "Button A: X+%i, Y+%i", &ax, &ay );
		std::sscanf( sb.c_str(), "Button B: X+%i, Y+%i", &bx, &by );
		std::sscanf( sp.c_str(), "Prize: X=%i, Y=%i", &px, &py );

		int price{ std::numeric_limits< int >::max() };

		for( int a{ 0 }; a != 101; ++a )
			for( int b{ 0 }; b != 101; ++b )
				if( ( ( ( a * ax ) + ( b * bx ) ) == px )
					&& ( ( ( a * ay ) + ( b * by ) ) == py ) )
				{
					price = std::min( price, a * 3 + b );
				}

		if( price != std::numeric_limits< int >::max() )
			total_price += price;
	}

	std::cout << "result = " << total_price << std::endl;

	return 0;
}