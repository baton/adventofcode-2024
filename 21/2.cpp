#include <iostream>
#include <fstream>
#include <iterator>
#include <string>
#include <string_view>
#include <vector>
#include <list>
#include <memory>
#include <set>
#include <map>
#include <numeric>
#include <limits>


size_t constexpr max_depth{ 25 };


using pad_t = std::vector< std::string >;
using point_t = std::pair< int, int >;
using pos_t = std::pair< pad_t const *, point_t >;

pad_t const numpad
{
	"789",
	"456",
	"123",
	" 0A"
};

pad_t const dirpad
{
	" ^A",
	"<v>"
};

std::map< char, point_t > const dirs
{
	{ '^', {  0, -1 } },
	{ '>', {  1,  0 } },
	{ 'v', {  0,  1 } },
	{ '<', { -1,  0 } },
};

point_t operator+( point_t const & a, point_t const & b ) noexcept
{
	return { a.first + b.first, a.second + b.second };
}

char const & at( pos_t const & pos ) noexcept
{
	return ( *pos.first )[ pos.second.second ][ pos.second.first ];
}

point_t const position( char const c, pad_t const & pad )
{
	for( int y{ 0 }; y != pad.size(); ++y )
		for( int x{ 0 }; x != pad[ y ].size(); ++x )
			if( pad[ y ][ x ] == c )
				return { x ,y };
	return { -1, -1 };
}

bool valid( point_t const & a, pad_t const & pad ) noexcept
{
	return ( a.first >= 0 ) && ( a.second >= 0 )
		&& ( a.second < pad.size() ) && ( a.first < pad[ a.second ].size() )
		&& ( pad[ a.second ][ a.first ] != ' ' );
}

pad_t const & get_pad( size_t const depth )
{
	return ( depth == max_depth ) ? numpad : dirpad;
}


std::vector< std::string > paths( pad_t const & pad, point_t const & a, point_t const & b )
{
	std::vector< std::string > v;

	size_t const max_length{ pad.size() + pad[ 0 ].size() - 2 };

	std::list< std::pair< point_t, std::string > > front;
	front.emplace_back( a, "" );

	while( !front.empty() )
	{
		auto [ x, s ]{ front.front() };
		front.pop_front();

		if( x == b )
		{
			v.push_back( s );
			continue;
		}

		if( !valid( x, pad ) )
			continue;

		if( s.size() == max_length )
			continue;

		for( auto [ c, d ] : dirs )
			front.emplace_back( x + d, s + c );
	}

	return v;
}


using cache_t = std::map< std::pair< size_t, std::pair< point_t, point_t > >, uint64_t >;
cache_t cache;


uint64_t calc( size_t const d, point_t const & a, point_t const & b )
{
	auto ci{ cache.find( { d, { a, b } } ) };
	if( ci != cache.end() )
		return ci->second;

	uint64_t min_length{ std::numeric_limits< uint64_t >::max() };

	for( std::string const s : paths( get_pad( d ), a, b ) )
	{
		if( d == 0 )
		{
			if( ( s.size() + 1 ) < min_length )
				min_length = s.size() + 1;
		}
		else
		{
			pad_t const & pad{ get_pad( d - 1 ) };
			point_t p{ position( 'A', pad ) };
			uint64_t len{ 0 };
			for( char const c : ( s + 'A' ) )
			{
				point_t q{ position( c, pad ) };
				len += calc( d - 1, p, q );
				p = q;
			}
			if( len < min_length )
				min_length = len;
		}
	}

	cache.insert( { { d, { a, b } }, min_length } );

	return min_length;
}


uint64_t path_len( std::string const & code )
{
	uint64_t min_length{ 0 };

	point_t p{ position( 'A', numpad ) };
	for( char const c : code )
	{
		point_t q{ position( c, numpad ) };
		min_length += calc( max_depth, p, q );
		p = q;
	}

	return min_length;
}


int main( int argc, char * argv[] )
{
	if( argc < 2 )
		return 0;

	std::ifstream ifs( argv[ 1 ] );

	uint64_t const result{
		std::transform_reduce(
			std::istream_iterator< std::string >( ifs ), std::istream_iterator< std::string >(),
			0ULL,
			std::plus(),
			[]( std::string const & s ) -> uint64_t
			{
				return path_len( s ) * std::stoull( s.substr( 0, 3 ) );
			}
		)
	};

	std::cout << "result = " << result << std::endl;

	return 0;
}