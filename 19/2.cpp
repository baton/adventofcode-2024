#include <iostream>
#include <fstream>
#include <set>
#include <map>
#include <string>
#include <string_view>


size_t match( std::string_view const s, std::set< std::string_view > const & p, std::map< std::string_view, size_t > & c )
{
	if( s.empty() )
		return 1;

	auto i{ c.find( s ) };
	if( i != c.end() )
		return i->second;

	size_t matches{ 0 };

	for( size_t l{ 1 }; l != s.length() + 1; ++l )
		if( p.count( s.substr( 0, l ) ) )
			matches += match( s.substr( l ), p, c );

	c.emplace( s, matches );

	return matches;
}

size_t count_matches( std::string_view const s, std::set< std::string_view > const & p )
{
	std::map< std::string_view, size_t > cache;

	return match( s, p, cache );
}


int main( int argc, char * argv[] )
{
	if( argc < 2 )
		return 0;

	std::ifstream ifs( argv[ 1 ] );

	std::set< std::string_view > patterns;

	std::string patterns_str;
	std::getline( ifs, patterns_str );

	std::string::size_type b{ 0 }, e{ 0 };
	while( true )
	{
		e = patterns_str.find( ", ", b );
		if( e == std::string::npos )
		{
			patterns.emplace( patterns_str.c_str() + b );
			break;
		}
		else
		{
			patterns.emplace( patterns_str.c_str() + b, e - b );
			b = e + 2;
		}
	}

	std::string t;
	std::getline( ifs, t );

	size_t count{ 0 };

	for( std::string s; std::getline( ifs, s ); )
		count += count_matches( s, patterns );

	std::cout << "result = " << count << std::endl;

	return 0;
}