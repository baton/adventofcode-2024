#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <string_view>
#include <iterator>


int main( int argc, char * argv[] )
{
	if( argc < 2 )
		return 0;

	std::ifstream ifs( argv[ 1 ] );

	std::vector< std::string > const data{ std::istream_iterator< std::string >( ifs ), std::istream_iterator< std::string >() };

	size_t count{ 0 };
	for( int y{ 1 }; y != data.size() - 1; ++y )
		for( int x{ 1 }; x != data[ y ].size() - 1; ++x )
			if( data[ y ][ x ] == 'A' )
			{
				if(      ( data[ y - 1 ][ x - 1 ] == 'M' ) && ( data[ y - 1 ][ x + 1 ] == 'M' )
					&&   ( data[ y + 1 ][ x - 1 ] == 'S' ) && ( data[ y + 1 ][ x + 1 ] == 'S' ) )
					++count;
				else if( ( data[ y - 1 ][ x - 1 ] == 'S' ) && ( data[ y - 1 ][ x + 1 ] == 'M' )
					&&   ( data[ y + 1 ][ x - 1 ] == 'S' ) && ( data[ y + 1 ][ x + 1 ] == 'M' ) )
					++count;
				else if( ( data[ y - 1 ][ x - 1 ] == 'S' ) && ( data[ y - 1 ][ x + 1 ] == 'S' )
					&&   ( data[ y + 1 ][ x - 1 ] == 'M' ) && ( data[ y + 1 ][ x + 1 ] == 'M' ) )
					++count;
				else if( ( data[ y - 1 ][ x - 1 ] == 'M' ) && ( data[ y - 1 ][ x + 1 ] == 'S' )
					&&   ( data[ y + 1 ][ x - 1 ] == 'M' ) && ( data[ y + 1 ][ x + 1 ] == 'S' ) )
					++count;
			}

	std::cout << "result = " << count << std::endl;

	return 0;
}
