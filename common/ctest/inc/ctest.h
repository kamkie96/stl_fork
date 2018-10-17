#include <stdio.h>
#include <string.h>

static int failed;
static int success;

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_DEFAULT "\x1b[0m"

#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

#define _toString(x) #x
#define toString(x) _toString(x)

#define PRINT_FAIL(file, function, line, fmt, first_variable, operator, second_variable) \
    do { \
        printf(ANSI_COLOR_RED "[ FAILED  ]  %s:%s:%d (" fmt " %s " fmt ")\n" ANSI_COLOR_DEFAULT, \
        file, function, line, first_variable, toString(operator), second_variable); \
    } while (0)

#define PRINT_SUCCESS(file, function, line, fmt, first_variable, operator, second_variable) \
    do { \
        printf(ANSI_COLOR_GREEN "[ SUCCESS ]  %s:%s:%d (" fmt " %s " fmt ")\n" ANSI_COLOR_DEFAULT, \
        file, function, line, first_variable, toString(operator), second_variable); \
    } while (0)

#define TEST_ASSERT(a, b, type, fmt, op) \
    do { \
        type _a = (a); \
        type _b = (b); \
        if (!(_a op _b)) \
        { \
            ++failed; \
            PRINT_FAIL(__FILENAME__, __func__, __LINE__, fmt, a, op, b); \
        } \
        else \
        { \
            ++success; \
            PRINT_SUCCESS(__FILENAME__, __func__, __LINE__, fmt, a, op, b); \
        } \
    } while (0)

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
        printf(ANSI_COLOR_GREEN "Passed tests : %d\n" \
               ANSI_COLOR_RED "Failed tests : %d\n" ANSI_COLOR_DEFAULT, \
               success, failed); \
    } while (0)

#define ASSERT_INT(a, b, op) TEST_ASSERT(a, b, int, "%d", op)
#define EQUALS_INT(a, b) ASSERT_INT(a, b, ==)
#define NOT_EQUALS_INT(a, b) ASSERT_INT(a, b, !=)
#define BIGGER_INT(a, b) ASSERT_INT(a, b, >)
#define SMALLER_INT(a, b) ASSERT_INT(a, b, <)

#define ASSERT_DOUBLE(a, b, op) TEST_ASSERT(a, b, double, "%lf", op)
#define EQUALS_DOUBLE(a, b) ASSERT_DOUBLE(a, b, ==)
#define NOT_EQUALS_DOUBLE(a, b) ASSERT_DOUBLE(a, b, !=)
#define BIGGER_DOUBLE(a, b) ASSERT_DOUBLE(a, b, >)
#define SMALLER_DOUBLE(a, b) ASSERT_DOUBLE(a, b, <)

/* need to be fix
 * to comapre two strings, should be use strcmp()
 * to measure length of two strings, should be use strlen()
 */
#define ASSERT_STRING(a, b, op) TEST_ASSERT(a, b, const char*, "%s", op)
#define EQUALS_STRING(a, b) ASSERT_STRING(a, b, ==)
#define NOT_EQUALS_STRING(a, b) ASSERT_STRING(a, b, !=)
#define BIGGER_STRING(a, b) ASSERT_STRING(a, b, >)
#define SMALLER_STRING(a, b) ASSERT_STRING(a, b, <)

#define ASSERT_SIZE_T(a, b, op) TEST_ASSERT(a, b, size_t, "%zu", op)
#define EQUALS_SIZE_T(a, b) ASSERT_SIZE_T(a, b, ==)
#define NOT_EQUALS_SIZE_T(a, b) ASSERT_SIZE_T(a, b, !=)
#define BIGGER_SIZE_T(a, b) ASSERT_SIZE_T(a, b, >)
#define SMALLER_SIZE_T(a, b) ASSERT_SIZE_T(a, b, <)
