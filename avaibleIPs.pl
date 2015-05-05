#!/usr/bin/perl

use warnings;
use strict;

my ($start,$end,$out,$IP,$tmp);

if(@ARGV < 2){
	die "Error, Usage: nameScript.pl StartIP EndIP \n";
}
$IP=$ARGV[0];
$ARGV[0] =~ /[\d]+.[\d]+.[\d]+.([\d]+)/g;
$start = $1;
$ARGV[1] =~ /[\d]+.[\d]+.[\d]+.([\d]+)/g;
$end = $1;
$tmp=$start;
while($tmp < $end ){
	$out = qx/ping -c 3 -w 4 $IP/;
	
	if($out =~ /100% packet loss/g){
       		print "$IP AVAIBLE\n";
	}elsif($out =~ /0% packet loss/g){
        	print "$IP NO AVAIBLE\n";
	}

	$tmp++;
	$IP =~ s/([\d]+).([\d]+).([\d]+).$start/$1.$2.$3.$tmp/g;
	$start=$tmp;
}
