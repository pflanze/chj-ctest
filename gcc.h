#ifndef GCC_H_
#define GCC_H_

// https://stackoverflow.com/questions/38499462/how-to-tell-clang-to-stop-pretending-to-be-other-compilers
// gcc - How to tell Clang to stop pretending to be other compilers? - Stack Overflow.html

#if defined(__GNUC__) && !defined(__llvm__) && !defined(__INTEL_COMPILER)
#define __GCC__   __GNUC__ // probably
#endif

#endif /* GCC_H_ */
