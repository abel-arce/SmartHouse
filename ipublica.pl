#!/usr/bin/perl 
$interfaz = $ARGV[0];

@iprivada= split("font",`GET ip.interchile.com`);
@_ip2 = split(">",$iprivada[1]);
@_ip = split("<",$_ip2[1]); 
$ip= $_ip[0];

@ipprivada = `ifconfig $interfaz | grep inet`;
my @ipprivada3=split(":", $ipprivada[0]);
my @ipprivada4=split(" ", @ipprivada3[1]);
$ipprivada=@ipprivada4[0];

print "   Ip Publica: $ip\n";
print "   Ip Privada: $ipprivada\n";
