#include <stdio.h>
#include "test.h"


void __test_assert_eq_failure(const char* file, int line,
                              const char* e1, const char* e2) {
    printf("* test failure in %s line %i:\r\n", file, line);
    printf("   %s == %s\r\n", e1, e2);
}

void run_test(test_function_t test) {
    struct TestStatistics stats = { 0, 0 };
    test(&stats);
    printf("==> %i success(es), %i failure(s)\r\n",
           stats.num_successes,
           stats.num_failures);
}
