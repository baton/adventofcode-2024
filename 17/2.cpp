#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>


std::vector< int64_t > run( int64_t a, std::vector< int64_t > const & p )
{
	int64_t b{ 0 }, c{ 0 };

	auto combo{
		[ &a, &b, &c ]( int64_t const x ) -> int64_t
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

	std::vector< int64_t > out;

	int64_t ip{ 0 };
	while( ip != p.size() )
	{
		int64_t const opcode{ p[ ip ] };
		int64_t const operand{ p[ ip + 1 ] };

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
				b = a / ( 1LL << combo( operand ) ); break;
			case 7:
				c = a / ( 1LL << combo( operand ) ); break;

			default:
				break;
		}

		ip += 2;
	}

	return out;
}

int64_t calc_a( int64_t a, int64_t i, std::vector< int64_t > const & p )
{
	for( int64_t x{ 0 }; x != 8; ++x )
	{
		int64_t const aa{ a + ( 1LL << ( i * 3 ) ) * x };
		if( aa < ( 1LL << ( ( p.size() - 1 ) * 3 ) ) )
			continue;

		std::vector< int64_t > const r{ run( aa, p ) };
		if( ( r.size() >= i ) && ( r[ i ] == p[ i ] ) )
		{
			if( i == 0 )
				return aa;

			int64_t const aaa{ calc_a( aa, i - 1, p ) };
			if( aaa != -1 )
				return aaa;
		}
	}

	return -1;
}


int main( int argc, char * argv[] )
{
	if( argc < 2 )
		return 0;

	std::vector< int64_t > p;

	std::ifstream ifs( argv[ 1 ] );
	std::string s;
	std::getline( ifs, s );
	std::getline( ifs, s );
	std::getline( ifs, s );
	std::getline( ifs, s );
	std::getline( ifs, s );
	std::istringstream iss( s.substr( 9 ) );
	for( char c[ 4 ]{}; iss.getline( c, sizeof( c ), ',' ); )
		p.push_back( std::atoll( c ) );

	int64_t const a{ calc_a( 0, p.size() - 1, p ) };

	std::cout << "a = " << a << std::endl;

	return 0;
}