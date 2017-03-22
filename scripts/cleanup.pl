#!/usr/bin/perl

$include=$ARGV[0];
$output=$ARGV[1];

process_file($include, $output);

#opendir(DIR, $include) or die $!;

#while (my $file=readdir(DIR)) {
#	next unless ($file =~ m/.h$/);

#	print "Note: Processing header file $file\n";
#	process_file("$include/$file", "$output/$file");
#}

exit(0);

sub process_file {
	my($src,$dst) = @_;
	my($output) = 1;

	open(my $in, "<", $src) or die "Failed to open source file $!";
	open(my $out, ">", $dst) or die "Failed to open output file $!";

	while (<$in>) {
		my($line) = $_;
	
		if ($line =~ /<vendor>/) {
			$output--;
		} elsif ($line =~ /<\/vendor>/) {
			$output++;
		} elsif ($output > 0) {
			$line =~ s/:\s+public\s+vendor::.*<T>\s+/: public T /g;
			$line =~ s/:\s+public\s+vendor::[^{]+//g;
			print $out "$line";
		}
	}

	close($in);
	close($out);
}

