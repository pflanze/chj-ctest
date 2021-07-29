# Copyright 2021 by Christian Jaeger <ch@christianjaeger.ch>
# Published under the same terms as perl itself
#

=head1 NAME

Chj::CTest

=head1 SYNOPSIS

=head1 DESCRIPTION

=head1 SEE ALSO

=cut


package Chj::CTest;
use strict;
use utf8;
use warnings;
use warnings FATAL => 'uninitialized';
use experimental 'signatures';
use Exporter "import";

our @EXPORT=qw();
our @EXPORT_OK=qw(path_to_FIL);
our %EXPORT_TAGS=(default => \@EXPORT, all=>[@EXPORT,@EXPORT_OK]);

sub path_to_FIL($path) {

    $path =~ s/\.c\z//
        or die "need a file with suffix .c, got '$path'";

    $path = "./$path" unless $path =~ m{/};
    
    $path=~ tr{./-}{D_M};

    $path=~ /^\w+\z/
        or die "after mangling, path still contains non-word characters: '$path'";

    $path."_"
}


1
