#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <list>
#include <set>
#include <string>
#include <memory>


int main( int argc, char * argv[] )
{
	if( argc < 2 )
		return 0;

	int a{ 0 }, b{ 0 }, c{ 0 };
	std::vector< int > p;

	std::ifstream ifs( argv[ 1 ] );
	std::string s;
	std::getline( ifs, s );
	a = std::stoll( s.substr( 12 ) );
	std::getline( ifs, s );
	b = std::stoll( s.substr( 12 ) );
	std::getline( ifs, s );
	c = std::stoll( s.substr( 12 ) );
	std::getline( ifs, s );
	std::getline( ifs, s );
	std::istringstream iss( s.substr( 9 ) );
	for( char c[ 4 ]{}; iss.getline( c, sizeof( c ), ',' ); )
		p.push_back( std::atoll( c ) );

	std::vector< int > out;

	auto combo{
		[ &a, &b, &c ]( int const x ) -> int
		{
			switch( x )
			{
				case 0:
				case 1:
				case 2:
				case 3:
					return x;
				case 4:
					return a;
				case 5:
					return b;
				case 6:
					return c;
				default:
					return 0;
			}
		}
	};

	int ip{ 0 };
	while( ip != p.size() )
	{
		int const opcode{ p[ ip ] };
		int const operand{ p[ ip + 1 ] };

		switch( opcode )
		{
			case 0:
				a /= 1LL << combo( operand ); break;
			case 1:
				b ^= operand; break;
			case 2:
				b = combo( operand ) & 7; break;
			case 3:
				if( a != 0 )
					ip = operand - 2;
				break;
			case 4:
				b ^= c; break;
			case 5:
				out.push_back( combo( operand ) & 7 ); break;
			case 6:
				b = a / ( 1 << combo( operand ) ); break;
			case 7:
				c = a / ( 1 << combo( operand ) ); break;

			default:
				return 0;
		}

		ip += 2;
	}

	for( int const o : out )
		std::cout << o << ",";

	return 0;
}