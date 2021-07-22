# How unit testing works

`test.h` defines `TEST` macro.

You use `TEST(shortname) { .... ASSERT_EQ(a,b) ... }`. You can use a short name, it is quasi-local to the file: the file name is being made part of the symbol name, via the Makefile:

    target/%.s: %.c
        cc65 $(CFLAGS) -DFIL=`basename $< .c`_ -o $@ $<

`make .deps` will also update `run_tests.c`, i.e. collect all TEST cases
and build a function that calls all of them. `run_tests.h` has the
prototype, include in whatever binary and run it there.
