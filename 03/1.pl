#

use strict;
use bignum;

my @a = ();
push @a, m/mul\(\d\d?\d?,\d\d?\d?\)/g while( <> );

my $sum = 0;
for( @a )
{
	$sum += int($1) * int($2) if( m/\((\d\d?\d?),(\d\d?\d?)\)/ );
}

print "result = $sum\n";
