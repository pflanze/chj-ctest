#include <stdio.h>
#include "test.h"


void __test_assert_eq_failure(const char* file, int line,
                              const char* e1, const char* e2) {
    printf("* test failure in %s line %i:\r\n"
           "   %s == %s\r\n",
           file, line,
           e1, e2);
}

void __test_assert_eq_fmt16_failure(const char* fmt,
                                    const char* file, int line,
                                    const char* e1, const char* e2,
                                    uint16_t v1, uint16_t v2) {
    __test_assert_eq_failure(file, line, e1, e2);
    printf("   ");
    printf(fmt, v1);
    printf(" == ");
    printf(fmt, v2);
    printf("\r\n");
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
    printf("\r\n");
}



void run_test_(struct TestStatistics* stats,
               const char* testname_file,
               test_function_t test) {
    printf("Running test %s ..\r\n", testname_file);
    test(stats);
}

void print_teststatistics(const struct TestStatistics* stats) {
    printf("==> %i success(es), %i failure(s)\r\n",
           stats->num_successes,
           stats->num_failures);
}

void run_test(const char* testname_file, test_function_t test) {
    struct TestStatistics stats = { 0, 0 };
    run_test_(&stats, testname_file, test);
    print_teststatistics(&stats);
}
