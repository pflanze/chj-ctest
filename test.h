
struct TestStatistics {
    int num_successes;
    int num_failures;
};


#define TEST__(file, name) void __test_##file##name(struct TestStatistics *__test_stats)
#define TEST_(file, name) TEST__(file, name)
#define TEST(name) TEST_(FIL, name)

// How can we generically print the result? In gcc we can get the type
// and statically dispatch, but here? Simply can't, right. Could as
// well always use ASSERT.
#define ASSERT_EQ(e1, e2) do {                                  \
        if ((e1) == (e2)) {                                     \
            __test_stats->num_successes++;                      \
        } else {                                                \
            __test_stats->num_failures++;                       \
            __test_assert_eq_failure(__FILE__, __LINE__, #e1, #e2);      \
        }                                                       \
    } while (0)


typedef void (*test_function_t)(struct TestStatistics *__test_stats);

void run_test_(struct TestStatistics* stats,
               const char* testname_file,
               test_function_t test);
void print_teststatistics(const struct TestStatistics* stats);

void run_test(const char* testname_file, test_function_t test);

// used from ASSERT_EQ macro
void __test_assert_eq_failure(const char* file, int line,
                              const char* e1, const char* e2);

