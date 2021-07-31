* both collection of TEST, and of dependencies, requires 'parsing' of
  the .c .h files, so, do both in the same program.
  
* `target/` is used to build, flat. Every basename (both .c and .s)
  can only appear once across *all* used libraries currently. This is
  nuts of course, just the status quo for right now.
  
* we find the list of all .o files that need to be build *also* from
  the same dependency information that is collected from 'parsing' the
  .h and .c files. We simply expect that the dir+basename of .h files
  and belonging .c files is the same. Also, we expect that each .s
  file has a corresponding .h file that's included by the programs
  that use the routines in the .s file (sounds reasonable).

