#!/usr/bin/perl
#****************************************************************************
#* stringify.pl
#*
#* Converts a text file into a C string with embedded double quotes escaped
#****************************************************************************

$array_name = $ARGV[0];

print "const char *$array_name = \n";

while (my $line = <STDIN>) {
	chomp $line;
	
	$line =~ s/"/\\"/g;
	
	print "\"$line\\n\"\n";
}

print ";\n";
