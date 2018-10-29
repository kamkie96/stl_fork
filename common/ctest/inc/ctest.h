#include <stdio.h>
#include <stddef.h>
#include <string.h>

static int failed;
static int success;

#define __ANSI_COLOR_RED     "\x1b[31m"
#define __ANSI_COLOR_GREEN   "\x1b[32m"
#define __ANSI_COLOR_DEFAULT "\x1b[0m"

#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

#define __toString(x) #x
#define _toString(x) __toString(x)

#define __PRINT_FAIL(file, function, line, fmt, first_variable, operator, second_variable) \
    do { \
        printf(__ANSI_COLOR_RED "[ FAILED  ]  %s:%s:%d (" fmt " %s " fmt ")\n" __ANSI_COLOR_DEFAULT, \
        file, function, line, first_variable, _toString(operator), second_variable); \
    } while (0)

#define __PRINT_SUCCESS(file, function, line, fmt, first_variable, operator, second_variable) \
    do { \
        printf(__ANSI_COLOR_GREEN "[ SUCCESS ]  %s:%s:%d (" fmt " %s " fmt ")\n" __ANSI_COLOR_DEFAULT, \
        file, function, line, first_variable, _toString(operator), second_variable); \
    } while (0)

#define __COMPARATOR(a, b) (a >= b ? 1 - (a == b) : -1)

#define __ASSERT(a, b, cmp, type, fmt, op) \
    do { \
        type _a = (a); \
        type _b = (b); \
        if (cmp(a, b) op 0) \
        { \
            ++success; \
            __PRINT_SUCCESS(__FILENAME__, __func__, __LINE__, fmt, _a, op, _b); \
        } \
        else \
        { \
            ++failed; \
            __PRINT_FAIL(__FILENAME__, __func__, __LINE__, fmt, _a, op, _b); \
        } \
    } while (0)

#define _ASSERT(a, b, cmp, type, fmt) __ASSERT(a, b, cmp, type, fmt, >=)

#define ASSERT_INT(a, b) _ASSERT(a, b, __COMPARATOR, int, "%d")
#define ASSERT_STR(a, b) _ASSERT(a, b, strcmp, const char*, "%s")
#define ASSERT_PTR(a, b) _ASSERT(a, b, __COMPARATOR, void*, "%p")
#define ASSERT_SIZE_T(a, b) _ASSERT(a, b, __COMPARATOR, size_t, "%zu")

#define __EXPECT(a, func, type, fmt, op) \
    do { \
        type _a = (a); \
        if (_a op func) \
        { \
            ++success; \
            __PRINT_SUCCESS(__FILENAME__, __func__, __LINE__, fmt, _a, op, func); \
        } \
        else \
        { \
            ++failed; \
            __PRINT_FAIL(__FILENAME__, __func__, __LINE__, fmt, _a, op, func); \
        } \
    } while (0) \

#define _EXPECT(a, func, type, fmt) __EXPECT(a, func, type, fmt, ==)

#define EXPECT_INT(a, func) _EXPECT(a, func, int, "%d")
#define EXPECT_SIZE_T(a, func) _EXPECT(a, func, size_t, "%zu")
#define EXPECT_STR(a, func) _EXPECT(a, func, const char*, "%s")

#define TEST(function) \
    do { \
        function; \
    } while (0)

#define BEGIN() \
    do { \
        success = failed = 0; \
    } while (0)

#define SUMMARY() \
    do { \
        printf(__ANSI_COLOR_GREEN "Passed tests : %d\n" \
               __ANSI_COLOR_RED "Failed tests : %d\n" __ANSI_COLOR_DEFAULT, \
               success, failed); \
    } while (0)

