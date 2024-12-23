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
point_t const numpad_default{ 2, 3 };
pos_t const numpad_start{ &numpad, numpad_default };

pad_t const dirpad
{
	" ^A",
	"<v>"
};
point_t const dirpad_default{ 2, 0 };
pos_t const dirpad_start{ &dirpad, dirpad_default };

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

bool valid( point_t const & a, pad_t const & pad ) noexcept
{
	return ( a.first >= 0 ) && ( a.second >= 0 )
		&& ( a.second < pad.size() ) && ( a.first < pad[ a.second ].size() )
		&& ( pad[ a.second ][ a.first ] != ' ' );
}


uint64_t path_len( std::string const & code )
{
	uint64_t min_length{ std::numeric_limits< uint64_t >::max() };

	std::list< std::pair< std::string_view, std::vector< pos_t > > > front;
	front.push_back( { code, { dirpad_start, dirpad_start, numpad_start } } );

	std::map< std::pair< std::string_view, std::vector< pos_t > >, size_t > lengths;
	lengths.emplace( front.front(), 0ULL );

	while( !front.empty() )
	{
		auto const [ s, pp ]{ front.front() };
		front.pop_front();

		if( s.empty() )
		{
			auto i{ lengths.find( { s, pp } ) };
			if( ( i != lengths.end() ) && ( i->second < min_length ) )
				min_length = i->second;

			continue;
		}

		for( auto const & [ c, d ] : dirs )
		{
			point_t const a{ pp.front().second + d };
			if( valid( a, *pp.front().first ) )
			{
				std::vector< pos_t > ppn{ pp };
				ppn.front().second = a;
				if( !lengths.count( { s, ppn } ) )
				{
					lengths[ { s, ppn } ] = lengths[ { s, pp } ] + 1;
					front.push_back( { s, ppn } );
				}
			}
		}

		size_t i{ 0 };
		while( ( i != ( pp.size() - 1 ) ) && ( at( pp[ i ] ) == 'A' ) )
			++i;

		if( i == ( pp.size() - 1 ) )
		{
			if( at( pp[ i ] ) == s[ 0 ] )
			{
				if( !lengths.count( { s.substr( 1 ), pp } ) )
				{
					lengths[ { s.substr( 1 ), pp } ] = lengths[ { s, pp } ] + 1;
					front.push_back( { s.substr( 1 ), pp } );
				}
			}
		}
		else
		{
			point_t const a{ pp[ i + 1 ].second + dirs.at( at( pp[ i ] ) ) };
			if( valid( a, *pp[ i + 1 ].first ) )
			{
				std::vector< pos_t > ppn{ pp };
				ppn[ i + 1 ].second = a;
				if( !lengths.count( { s, ppn } ) )
				{
					lengths[ { s, ppn } ] = lengths[ { s, pp } ] + 1;
					front.push_back( { s, ppn } );
				}
			}
		}
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