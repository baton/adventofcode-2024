#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <string_view>


int main( int argc, char * argv[] )
{
	if( argc < 2 )
		return 0;

	std::string s;
	std::ifstream ifs( argv[ 1 ] );
	ifs >> s;

	uint64_t sum{ 0 };
	std::string x;

	uint64_t id{ 0 }, pos{ 0 }, last_id{ s.length() / 2 + 1 }, last_len{ 0 };
	std::string_view sv( s );
	while( sv.length() > 1 )
	{
		uint64_t f{ static_cast< uint64_t >( sv[ 0 ] - '0' ) };
		uint64_t b{ static_cast< uint64_t >( sv[ 1 ] - '0' ) };
		sv = sv.substr( 2 );

		while( f )
		{
			sum += id * pos++;
			--f;
		}

		++id;

		while( b )
		{
			if( last_len )
			{
				sum += last_id * pos++;
				--last_len;
				--b;
			}
			if( !last_len && b && ( sv.length() > 1 ) )
			{
				last_len = static_cast< uint64_t >( sv.back() - '0' );
				--last_id;
				sv = sv.substr( 0, sv.length() - 2 );
			}
		}
	}

	uint64_t f{ static_cast< uint64_t >( sv[ 0 ] - '0' ) };
	while( f )
	{
		sum += id * pos++;
		--f;
	}
	while( last_len )
	{
		sum += last_id * pos++;
		--last_len;
	}

	std::cout << "result = " << sum << std::endl;

	return 0;
}
