#!/usr/bin/perl
#    https://www.youtube.com
use strict;
use warnings;

my $content;

$content = qx 'http https://github.com/abel-arce/SmartHouse/blob/master/ipublica.pl';

while($content =~ /(.\$[a-z]+)/g){
		print "$1\n";
}
