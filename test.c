/*
  Copyright (C) 2021 Christian Jaeger, <ch@christianjaeger.ch>
  Published under the terms of the MIT License, see the LICENSE file.
*/
#include <stdio.h>
#include "test.h"


void __test_assert_eq_failure(const char* file, int line,
                              const char* e1, const char* e2) {
    printf("* test failure in %s line %i:\n"
           "   %s == %s\n",
           file, line,
           e1, e2);
}

void __test_assert_eq_fmt16_failure(const char* fmt,
                                    const char* file, int line,
                                    const char* e1, const char* e2,
                                    uint16_t v1, uint16_t v2) {
    __test_assert_eq_failure(file, line, e1, e2);
    printf("   ");
#ifdef __GCC__
#pragma GCC diagnostic ignored "-Wformat-overflow"
#endif
    printf(fmt, v1);
    printf(" == ");
    printf(fmt, v2);
    printf("\n");
}
// copy-paste with type changed. Define via macro?
void __test_assert_eq_fmt32_failure(const char* fmt,
                                    const char* file, int line,
                                    const char* e1, const char* e2,
                                    uint32_t v1, uint32_t v2) {
    __test_assert_eq_failure(file, line, e1, e2);
    printf("   ");
    printf(fmt, v1);
    printf(" == ");
    printf(fmt, v2);
    printf("\n");
}



void run_test_(struct TestStatistics* stats,
               const char* testname_file,
               test_function_t test) {
    printf("- Test %s ...\n", testname_file);
    test(stats);
}

void print_teststatistics(const struct TestStatistics* stats) {
    printf("==> %s, %i success(es), %i failure(s)\n",
           stats->num_failures ? "FAIL" : "OK",
           stats->num_successes,
           stats->num_failures);
}

void run_test(const char* testname_file, test_function_t test) {
    struct TestStatistics stats = { 0, 0 };
    run_test_(&stats, testname_file, test);
    print_teststatistics(&stats);
}
