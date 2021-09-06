/*
  Copyright (C) 2021 Christian Jaeger, <ch@christianjaeger.ch>
  Published under the terms of the MIT License, see the LICENSE file.
*/
#ifndef TEST_H_
#define TEST_H_

#include <stdint.h>

struct TestStatistics {
    int num_successes;
    int num_failures;
};


#define TEST__(file, name) void __test_##file##name(struct TestStatistics *__test_stats)
#define TEST_(file, name) TEST__(file, name)

// Turn test code into a function that is going to be optimized away.
#define NOTEST(name) inline static void __test_##file##name(struct TestStatistics *__test_stats)

#ifdef noTEST
# define TEST(name) NOTEST(name)
#else
# define TEST(name) TEST_(FIL, name)
#endif

// How can we generically print the result? In gcc we can get the type
// and statically dispatch, but here? Simply can't, right. Could as
// well always use ASSERT.
#define ASSERT_EQ(e1, e2) do {                                          \
        if ((e1) == (e2)) {                                             \
            __test_stats->num_successes++;                              \
        } else {                                                        \
            __test_stats->num_failures++;                               \
            __test_assert_eq_failure(__FILE__, __LINE__, #e1, #e2);     \
        }                                                               \
    } while (0)

// only works for types up to int
#define ASSERT_EQ_(t, e1, e2) do {                                      \
        t __v1 = e1;                                                    \
        t __v2 = e2;                                                    \
        if (__v1 == __v2) {                                             \
            __test_stats->num_successes++;                              \
        } else {                                                        \
            __test_stats->num_failures++;                               \
            __test_assert_eq_fmt_failure_##t(__test_fmt_##t,            \
                                             __FILE__, __LINE__,        \
                                             #e1, #e2,                  \
                                             (__test_t_for_##t)__v1,    \
                                             (__test_t_for_##t)__v2);   \
        }                                                               \
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

void __test_assert_eq_fmt16_failure(const char* fmt,
                                    const char* file, int line,
                                    const char* e1, const char* e2,
                                    uint16_t v1, uint16_t v2);

void __test_assert_eq_fmt32_failure(const char* fmt,
                                    const char* file, int line,
                                    const char* e1, const char* e2,
                                    uint32_t v1, uint32_t v2);


typedef void * ptr;

#define  __test_assert_eq_fmt_failure_int __test_assert_eq_fmt16_failure
#define  __test_assert_eq_fmt_failure_int16_t __test_assert_eq_fmt16_failure
#define  __test_assert_eq_fmt_failure_uint16_t __test_assert_eq_fmt16_failure
#define  __test_assert_eq_fmt_failure_int8_t __test_assert_eq_fmt16_failure
#define  __test_assert_eq_fmt_failure_uint8_t __test_assert_eq_fmt16_failure
#define  __test_assert_eq_fmt_failure_bool __test_assert_eq_fmt16_failure
#define  __test_assert_eq_fmt_failure_ptr __test_assert_eq_fmt16_failure

#define  __test_assert_eq_fmt_failure_int32_t __test_assert_eq_fmt32_failure
#define  __test_assert_eq_fmt_failure_uint32_t __test_assert_eq_fmt32_failure


#define __test_fmt_int "%i"   
#define __test_fmt_int16_t "%i"
#define __test_fmt_uint16_t "%u"
#define __test_fmt_int8_t "%i" // XX?
#define __test_fmt_uint8_t "%i"
#define __test_fmt_bool "%i"
#define __test_fmt_ptr "%p"

#define __test_fmt_int32_t "%li"
#define __test_fmt_uint32_t "%li" // XX


#define __test_t_for_int uint16_t
#define __test_t_for_int16_t uint16_t
#define __test_t_for_uint16_t uint16_t
#define __test_t_for_int8_t uint16_t
#define __test_t_for_uint8_t uint16_t
#define __test_t_for_bool uint16_t
#define __test_t_for_ptr uint16_t

#define __test_t_for_int32_t int32_t
#define __test_t_for_uint32_t uint32_t

#endif /* TEST_H_ */
