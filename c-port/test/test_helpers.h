#ifndef TEST_HELPERS_H
#define TEST_HELPERS_H

#include <stdio.h>
#include <string.h>
#include <math.h>

static int tests_run = 0;
static int tests_failed = 0;

#define ASSERT_TRUE(cond) do { \
    tests_run++; \
    if (!(cond)) { \
        tests_failed++; \
        fprintf(stderr, "FAIL %s:%d: %s\n", __FILE__, __LINE__, #cond); \
    } \
} while (0)

#define ASSERT_EQ_INT(actual, expected) do { \
    tests_run++; \
    long _a = (long)(actual), _e = (long)(expected); \
    if (_a != _e) { \
        tests_failed++; \
        fprintf(stderr, "FAIL %s:%d: %s == %s (got %ld vs %ld)\n", \
                __FILE__, __LINE__, #actual, #expected, _a, _e); \
    } \
} while (0)

#define ASSERT_NEAR(actual, expected, eps) do { \
    tests_run++; \
    double _a = (double)(actual), _e = (double)(expected), _eps = (double)(eps); \
    if (fabs(_a - _e) > _eps) { \
        tests_failed++; \
        fprintf(stderr, "FAIL %s:%d: %s ~= %s (got %.6f vs %.6f, eps %.6f)\n", \
                __FILE__, __LINE__, #actual, #expected, _a, _e, _eps); \
    } \
} while (0)

#define ASSERT_STR_EQ(actual, expected) do { \
    tests_run++; \
    const char* _a = (actual); const char* _e = (expected); \
    if (_a == NULL || _e == NULL || strcmp(_a, _e) != 0) { \
        tests_failed++; \
        fprintf(stderr, "FAIL %s:%d: \"%s\" == \"%s\" (got \"%s\" vs \"%s\")\n", \
                __FILE__, __LINE__, #actual, #expected, \
                _a ? _a : "(null)", _e ? _e : "(null)"); \
    } \
} while (0)

#define RUN_TEST(fn) do { fn(); } while (0)

#define TEST_SUMMARY() do { \
    printf("%d assertions, %d failed\n", tests_run, tests_failed); \
    return tests_failed == 0 ? 0 : 1; \
} while (0)

#endif