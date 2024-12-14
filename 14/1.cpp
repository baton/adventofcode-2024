#include <iostream>
#include <fstream>
#include <string>


int main( int argc, char * argv[] )
{
	if( argc < 2 )
		return 0;

	std::ifstream ifs( argv[ 1 ] );

	int64_t constexpr t{ 100 };
	int64_t constexpr w{ 101 };
	int64_t constexpr h{ 103 };

	size_t q1{ 0 }, q2{ 0 }, q3{ 0 }, q4{ 0 };

	for( std::string s; std::getline( ifs, s ); )
	{
		int64_t x{ 0 }, y{ 0 }, vx{ 0 }, vy{ 0 };
		std::sscanf( s.c_str(), "p=%lli,%lli v=%lli,%lli", &x, &y, &vx, &vy );

		x = ( x + t * vx ) % w;
		if( x < 0 )
			x += w;
		y = ( y + t * vy ) % h;
		if( y < 0 )
			y += h;

		if( y < ( h / 2 ) )
		{
			if( x < ( w / 2 ) )
				++q1;
			else if( x > ( w / 2 ) )
				++q2;
		}
		else if( y > ( h / 2 ) )
		{
			if( x < ( w / 2 ) )
				++q3;
			else if( x > ( w / 2 ) )
				++q4;
		}
	}

	std::cout << "result = " << ( q1 * q2 * q3 * q4 ) << std::endl;

	return 0;
}