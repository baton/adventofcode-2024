#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>


struct robot_t
{
	int x{ 0 }, y{ 0 }, vx{ 0 }, vy{ 0 };
};


int main( int argc, char * argv[] )
{
	if( argc < 2 )
		return 0;

	std::ifstream ifs( argv[ 1 ] );

	int64_t constexpr w{ 101 };
	int64_t constexpr h{ 103 };

	size_t q1{ 0 }, q2{ 0 }, q3{ 0 }, q4{ 0 };
	
	std::vector< robot_t > robots;

	for( std::string s; std::getline( ifs, s ); )
	{
		robot_t r;
		std::sscanf( s.c_str(), "p=%i,%i v=%i,%i", &r.x, &r.y, &r.vx, &r.vy );
		robots.push_back( std::move( r ) );
	}

	size_t t{ 0 };
	for( ; t != 10000; ++t )
	{
		std::map< std::pair< int, int >, size_t > m;
		for( robot_t & r : robots )
		{
			++m[ { r.x, r.y } ];

			r.x += r.vx;
			r.x %= w;
			if( r.x < 0 )
				r.x += w;
			
			r.y += r.vy;
			r.y %= h;
			if( r.y < 0 )
				r.y += h;
		}

		size_t share{ 0 };
		for( int x{ w / 3 }; x != 2 * w / 3; ++x )
			for( int y{ h / 4 }; y != 3 * h / 4; ++y )
			{
				auto i{ m.find( { x, y } ) };
				if( i != m.end() )
					share += i->second;
			}
			
		if( share > ( robots.size() / 2 ) )
			break;
	}

	std::cout << "result = " << t << std::endl;

	return 0;
}