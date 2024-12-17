#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <set>
#include <string>
#include <memory>


std::pair< int, int > dir( char const c )
{
	switch( c )
	{
		case '^': return {  0, -1 };
		case '>': return {  1,  0 };
		case 'v': return {  0,  1 };
		case '<': return { -1,  0 };

		default: return {};
	}
}


int main( int argc, char * argv[] )
{
	if( argc < 2 )
		return 0;

	std::ifstream ifs( argv[ 1 ] );

	std::vector< std::string > m;

	for( std::string s; std::getline( ifs, s ) && !s.empty(); )
	{
		std::string & t{ m.emplace_back( "" ) };
		t.reserve( s.size() * 2 );
		for( char const c : s )
			switch( c )
			{
				case '#' : t.push_back( '#' ); t.push_back( '#' ); break;
				case 'O' : t.push_back( '[' ); t.push_back( ']' ); break;
				case '@' : t.push_back( '@' ); t.push_back( '.' ); break;
				case '.' : t.push_back( '.' ); t.push_back( '.' ); break;
				default: break;
			}
	}

	int const w{ static_cast< int >( m[ 0 ].size() ) };
	int const h{ static_cast< int >( m.size() ) };

	bool found{ false };
	size_t x{ 0 }, y{ 0 };
	for( ; x != w; ++x )
	{
		for( y = 0; y != h; ++y )
			if( found = ( m[ y ][ x ] == '@' ) )
				break;
		if( found )
			break;
	}

	for( std::string s; std::getline( ifs, s ); )
		for( char const c : s )
		{
			auto const [ dx, dy ]{ dir( c ) };
			if( ( c == '<' ) || ( c == '>' ) )
			{
				int l{ 1 };
				while( ( m[ y + dy * l ][ x + dx * l ] == '[' ) || ( m[ y + dy * l ][ x + dx * l ] == ']' ) )
					++l;
				if( m[ y + dy * l ][ x + dx * l ] == '.' )
				{
					while( l != 0 )
					{
						m[ y + dy * l ][ x + dx * l ] = ( l % 2 == ( ( c == '<' ) ? 1 : 0 ) ) ? '[' : ']';
						--l;
					}
					m[ y + dy ][ x + dx ] = '@';
					m[ y ][ x ] = '.';

					x += dx;
					y += dy;
				}
			}
			else if( m[ y + dy ][ x + dx ] == '.' )
			{
				m[ y + dy ][ x + dx ] = '@';
				m[ y ][ x ] = '.';

				x += dx;
				y += dy;
			}
			else if( m[ y + dy ][ x + dx ] != '#' )
			{
				using boxes_t = std::set< std::pair< int, int > >;
				boxes_t boxes;
				if( m[ y + dy ][ x ] == '[' )
					boxes.emplace( x, y + dy );
				else
					boxes.emplace( x - 1, y + dy );

				for( boxes_t bb; bb != boxes; )
				{
					bb = boxes;
					for( auto const & [ bx, by ] : bb )
					{
						if( m[ by + dy ][ bx ] == '[' )
							boxes.emplace( bx, by + dy );
						else if( m[ by + dy ][ bx ] == ']' )
							boxes.emplace( bx - 1, by + dy );

						if( m[ by + dy ][ bx + 1 ] == '[' )
							boxes.emplace( bx + 1, by + dy );
					}
				}

				auto can_move{
					[ &m, &boxes, &dy ]() -> bool
					{
						for( auto const & [ bx, by ] : boxes )
							if( ( m[ by + dy ][ bx ] == '#' )
								|| ( m[ by + dy ][ bx + 1 ] == '#' ) )
								return false;
						return true;
					}
				};

				if( can_move() )
				{
					for( auto const & [ bx, by ] : boxes )
					{
						m[ by ][ bx ] = '.';
						m[ by ][ bx + 1 ] = '.';
					}
					for( auto const & [ bx, by ] : boxes )
					{
						m[ by + dy ][ bx ] = '[';
						m[ by + dy ][ bx + 1 ] = ']';
					}

					m[ y + dy ][ x + dx ] = '@';
					m[ y ][ x ] = '.';

					x += dx;
					y += dy;
				}
			}
		}

	uint64_t sum{ 0 };
	for( size_t j{ 0 }; j != m.size(); ++j )
		for( size_t i{ 0 }; i != m[ j ].size(); ++i )
			if( m[ j ][ i ] == '[' )
				sum += j * 100 + i;

	std::cout << "result = " << sum << std::endl;

	return 0;
}