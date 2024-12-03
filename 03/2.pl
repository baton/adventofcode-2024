#

use strict;
use bignum;

my @a = ();
push @a, m/mul\(\d\d?\d?,\d\d?\d?\)|do\(\)|don\'t\(\)/g while( <> );

my $sum = 0;
my $enabled = 1;
for( @a )
{
	if( $_ eq "do()" )
	{
		$enabled = 1;
	}
	elsif( $_ eq "don't()" )
	{
		$enabled = 0;
	}
	elsif( m/\((\d\d?\d?),(\d\d?\d?)\)/ )
	{
		$sum += int($1) * int($2) if( $enabled );
	}
}

print "result = $sum\n";
