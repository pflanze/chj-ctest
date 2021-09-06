# Copyright (C) 2021 Christian Jaeger, <ch@christianjaeger.ch>
# Published under the terms of the MIT License, see the LICENSE file.

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
our @EXPORT_OK=qw(path_to_canonical_relpath path_to_FIL);
our %EXPORT_TAGS=(default => \@EXPORT, all=>[@EXPORT,@EXPORT_OK]);

sub path_to_canonical_relpath($path) {

    if ($path =~ m{/}) {
        $path =~ m{^/} and die "absolute paths not accepted: '$path'";
        $path =~ s{/+}{/}sg;
        do {} while $path =~ s{(^|/)\./}{$1}s;
        $path = "./$path" unless $path =~ m{/};
    } else {
        $path = "./$path";
    }
    
    $path
}

# main> path_to_canonical_relpath "././vm.h"
# $VAR1 = './vm.h';
# main> path_to_canonical_relpath "./../vm.h"
# $VAR1 = '../vm.h';
# main> path_to_canonical_relpath ".././vm.h"
# $VAR1 = '../vm.h';
# main> path_to_canonical_relpath "../././vm.h"
# $VAR1 = '../vm.h';
# main> path_to_canonical_relpath ".././foo./vm.h"
# $VAR1 = '../foo./vm.h';
# main> path_to_canonical_relpath ".././foo/./vm.h"
# $VAR1 = '../foo/vm.h';
# main> path_to_canonical_relpath "..//.///foo///.//vm.h"
# $VAR1 = '../foo/vm.h';

sub path_to_FIL($path) {
    my $p = path_to_canonical_relpath($path);
    
    $p =~ s/\.c\z//
        or die "need a file with suffix .c, got '$path'";

    $p=~ tr{./-}{D_M};

    $p=~ /^\w+\z/
        or die "after mangling, path still contains non-word characters: '$p'";

    $p."_"
}


1
