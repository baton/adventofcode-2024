#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <memory>
#include <vector>
#include <algorithm>


int main( int argc, char * argv[] )
{
	if( argc < 2 )
		return 0;

	std::string s;
	std::ifstream ifs( argv[ 1 ] );
	ifs >> s;

	std::set< std::pair< uint64_t, uint64_t > > blanks;
	std::vector< std::pair< uint64_t, uint64_t > > files;

	uint64_t p{ 0 };
	bool blank{ false };
	for( char const c : s )
	{
		uint64_t const l{ static_cast< uint64_t >( c - '0' ) };
		if( !blank )
			files.emplace_back( p, l );
		else
			blanks.emplace( p, l );

		p += l;

		blank = !blank;
	}

	for( auto f{ files.rbegin() }; f != files.rend(); ++f )
	{
		auto bi{ std::find_if( blanks.begin(), blanks.end(),
			[ &f ]( auto const & b ) -> bool
			{
				return ( b.first < f->first ) && ( f->second <= b.second );
			}
		) };
		if( bi != blanks.end() )
		{
			auto b{ *bi };
			blanks.erase( bi );
			f->first = b.first;
			b.first += f->second;
			b.second -= f->second;
			if( b.second != 0 )
				blanks.insert( std::move( b ) );
		}
	}

	uint64_t sum{ 0 };
	for( uint64_t id{ 0 }; id != files.size(); ++id )
	{
		for( uint64_t l{ 0 }; l != files[ id ].second; ++l )
			sum += id * ( files[ id ].first + l );
	}

	std::cout << "result = " << sum << std::endl;

	return 0;
}
