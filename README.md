# Simple unit testing and build system

This simple library aims to provide for a syntax for embedded unit
tests. It also contains a tool ([gendeps](bin/gendeps)) to collect
all unit test names of all files and generate a file to run all tests,
and as part of doing that it also generates dependency output for
make.

## Issues

This is experimental and doesn't work well yet.

* Walking dependencies is unfinished(?), it currently still needs a
  list of all OBJS (?). It should be enough to give just a single file
  for all dependencies to be found.

* `make clean` has to be called often. Make apparently can't deal with
  reading dependencies in the same run in which it generates them? May
  have to move to a frontend tool approach (call the wrapper instead
  of `make` directly, instead of calling `gendeps` from within the
  makefile).

* Files are not currently properly parsed for finding tests and
  dependencies, instead some simple regular expressions are used. This
  means that `TEST` forms are found even if disabled via preprocessor
  directives, or via commenting out if not done in the same line.

## Documentation

* [How unit testing works](doc/testing.md)
* [Principles](doc/principles.md)

## Licensing

Copyright (C) 2021 Christian Jaeger, <ch@christianjaeger.ch>

This is being published under the terms of the MIT License.
