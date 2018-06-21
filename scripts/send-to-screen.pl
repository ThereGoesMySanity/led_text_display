#!/usr/bin/perl

use IO::Socket::UNIX;
use HTML::Escape qw(escape_html);

print "Content-Type: text/plain\n\n";

my $SOCK_PATH = "/home/will/led-site/serv_socket";

my $client = IO::Socket::UNIX->new(
    Type => SOCK_STREAM(),
    Peer => $SOCK_PATH
);

die "$!" unless $client;

my @values = split(/&/, $ENV{QUERY_STRING});

my ($data, $color);

foreach my $i (@values) {
    my ($field, $value) = split(/=/, $i);
    if ($field eq "text") {
        $data = $value;
    }
    elsif ($field eq "color") { 
        $color = $value; 
    }
    print "$field = $value\n";
}

print $client "{\"text\": \"$data\", \"color\": \"$color\"}";
