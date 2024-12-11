#include <iostream>
#include <fstream>
#include <vector>
#include <map>
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

using cache_t = std::map< uint64_t, std::map< uint64_t, uint64_t > >;

uint64_t calc( uint64_t const stone, size_t const blinks, cache_t & cache )
{
	if( blinks == 0 )
		return 1;

	auto i{ cache[ blinks ].find( stone ) };
	if( i != cache[ blinks ].end() )
		return i->second;

	uint64_t val{ 0 };
	if( stone == 0 )
		val = calc( 1, blinks - 1, cache );
	else
	{
		uint64_t const r{ lg( stone ) };
		if( r % 2 == 0 )
		{
			uint64_t const p{ pg( r / 2 ) };
			val = calc( stone % p, blinks - 1, cache ) + calc( stone / p, blinks - 1, cache );
		}
		else
			val = calc( stone * 2024, blinks - 1, cache );
	}
	cache[ blinks ].emplace( stone, val );

	return val;
}


int main( int argc, char * argv[] )
{
	if( argc < 2 )
		return 0;

	std::ifstream ifs( argv[ 1 ] );
	std::vector< uint64_t > const stones{ std::istream_iterator< uint64_t >( ifs ), std::istream_iterator< uint64_t >() };

	cache_t cache;
	
	uint64_t count{ 0 };
	for( uint64_t const stone : stones )
		count += calc( stone, 75, cache );

	std::cout << "result = " << count << std::endl;

	return 0;
}