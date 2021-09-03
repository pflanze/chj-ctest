# How unit testing works

`test.h` defines `TEST` macro.

You use `TEST(name) { .... ASSERT_EQ(a,b) ... }`. You can use a short name, it is quasi-local to the file: the file name is being made part of the symbol name, via the Makefile:

    target/%.s: %.c
        cc65 $(CFLAGS) -DFIL=`../chj-ctest/bin/path-to-FIL $<` -o $@ $<

Also add the following to the Makefile:

    .deps:
	    ../chj-ctest/bin/gendeps $(OBJS) > .deps

`make .deps` will then also update `run_tests.c`, i.e. collect all
TEST cases and build a function that calls all of them. `run_tests.h`
has the prototype, include in whatever binary and run it there.

You can use `NOTEST`, as in `NOTEST(name) { ... }`, to turn off a
test, and you can set the `noTEST` environment variable and pass
`-DnoTEST` to the compiler to turn off all unit tests globally. (Note
that link-time optimizations (e.g. `gcc -flto`) may remove the test
code anyway if not called.)
