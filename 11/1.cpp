#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>


uint64_t lg( uint64_t x )
{
	uint64_t r{ 0 };
	while( x )
	{
		++r;
		x /= 10;
	}
	return r;
}

uint64_t pg( uint64_t x )
{
	uint64_t p{ 1 };
	while( x )
	{
		p *= 10;
		--x;
	}
	return p;
}


int main( int argc, char * argv[] )
{
	if( argc < 2 )
		return 0;

	std::ifstream ifs( argv[ 1 ] );
	std::vector< uint64_t > stones{ std::istream_iterator< uint64_t >( ifs ), std::istream_iterator< uint64_t >() };

	for( size_t blinks{ 0 }; blinks != 25; ++blinks )
	{
		std::vector< uint64_t > s2;
		for( uint64_t const s : stones )
		{
			if( s == 0 )
				s2.push_back( 1 );
			else
			{
				uint64_t const r{ lg( s ) };
				if( r % 2 == 0 )
				{
					uint64_t const p{ pg( r / 2 ) };
					s2.push_back( s / p );
					s2.push_back( s % p );
				}
				else
					s2.push_back( s * 2024 );
			}
		}
		stones = std::move( s2 );
	}

	std::cout << "result = " << stones.size() << std::endl;

	return 0;
}