#!/usr/bin/perl
use warnings;
use strict;

print("        Welcome to SmartHouse server\n");

my $out = qx/\.\/USB/;
print $out;

