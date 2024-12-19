#include <iostream>
#include <fstream>
#include <sstream>
#include <set>
#include <string>
#include <string_view>
#include <algorithm>


bool match( std::string_view const s, std::set< std::string_view > const & p )
{
	if( s.empty() )
		return true;

	std::set< std::string_view > f, v;
	f.insert( s );

	while( !f.empty() )
	{
		std::string_view x{ *f.begin() };
		f.erase( f.begin() );

		if( x.empty() )
			return true;

		if( !v.insert( x ).second )
			continue;

		for( size_t l{ 1 }; l != x.length() + 1; ++l )
			if( p.count( x.substr( 0, l ) ) )
				f.insert( x.substr( l ) );
	}

	return false;
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
		if( match( s, patterns ) )
			++count;

	std::cout << "result = " << count << std::endl;

	return 0;
}