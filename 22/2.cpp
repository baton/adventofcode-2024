#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <algorithm>


bool push( std::vector< int64_t > & seq, int64_t const x )
{
	if( seq.size() < 4 )
		seq.push_back( x );
	else
	{
		seq[ 0 ] = seq[ 1 ];
		seq[ 1 ] = seq[ 2 ];
		seq[ 2 ] = seq[ 3 ];
		seq[ 3 ] = x;
	}

	return seq.size() == 4;
}

constexpr size_t n( size_t const x ) noexcept
{
	return x % 10ULL;
}


int main( int argc, char * argv[] )
{
	if( argc < 2 )
		return 0;

	std::ifstream ifs( argv[ 1 ] );

	std::map< std::vector< int64_t >, size_t > sells;

	for( std::string s; std::getline( ifs, s ); )
	{
		size_t x{ std::stoull( s ) };
		std::vector< int64_t > seq;
		std::set< std::vector< int64_t > > got;
		for( size_t i{ 0 }, y{ x }; i != 2000; ++i )
		{
			y = x;
			x = ( x ^ ( x << 6 ) ) & 0xFFFFFFULL;
			x = ( x ^ ( x >> 5 ) ) & 0xFFFFFFULL;
			x = ( x ^ ( x << 11 ) ) & 0xFFFFFFULL;
			
			if( push( seq, n( x ) - n( y ) ) && got.insert( seq ).second )
				sells[ seq ] += n( x );
		}
	}

	auto const i{ std::max_element( sells.cbegin(), sells.cend(),
		[]( auto const & a, auto const & b ) -> bool { return a.second < b.second; } ) };

	std::cout << "result = " << i->second << std::endl;

	return 0;
}