#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <string_view>
#include <iterator>


std::string_view constexpr xmas{ "XMAS" };


int main( int argc, char * argv[] )
{
	if( argc < 2 )
		return 0;

	std::ifstream ifs( argv[ 1 ] );

	std::vector< std::string > const data{ std::istream_iterator< std::string >( ifs ), std::istream_iterator< std::string >() };

	size_t count{ 0 };
	for( int y{ 0 }; y != data.size(); ++y )
		for( int x{ 0 }; x != data[ y ].size(); ++x )
		{
			for( int dy{ -1 }; dy != 2; ++dy )
				for( int dx{ -1 }; dx != 2; ++dx )
				{
					bool found{ true };
					for( int i{ 0 }; i != xmas.length(); ++i )
						found &= ( ( y + i * dy ) >= 0 ) && ( ( y + i * dy ) < data.size() )
							&& ( ( x + i * dx ) >= 0 ) && ( ( x + i * dx ) < data[ y ].size() )
							&& ( data[ y + i * dy ][ x + i * dx ] == xmas[ i ] );
					if( found )
						++count;
				}
		}

	std::cout << "result = " << count << std::endl;

	return 0;
}
