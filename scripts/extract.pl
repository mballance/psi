#!/usr/bin/perl


sub process {
	my($fh, $input) = @_;
	my($output) = 0;
	my($in_undef) = 0;
	my($line);

	open(my $in_fh, "<", $input) or die "Failed to open file $input";

	while (<$in_fh>) {
		$line = $_;
		if ($output == 0) {
			if ($line =~ /class\s+[a-zA-Z0-9_]+\s+:/ ||
				$line =~ /class\s+[a-zA-Z0-0_]+\s+{/) {
				$output = 1;
			}
		} elsif ($line =~ /#ifdef UNDEFINED/) {
				$in_undef = 1;
				$output = 0;
		}

		if ($output) {
			print $fh $line;

			if ($line =~ /};/) {
				$output = 0;
			}
		} elsif ($in_undef && $line =~ /#endif/) {
			$in_undef = 0;
			$output = 1;
		}
	}
}

opendir(DIR, $ARGV[0]) or die $!;

while (my $file=readdir(DIR)) {
#	print "$file=$file";
	next unless ($file =~ m/.h$/);

	process(STDOUT, "$ARGV[0]/$file");
	print "\n";
}


