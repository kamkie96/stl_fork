#ifndef __DEBUG_PRINT_H__
#define __DEBUG_PRINT_H__

#include <stdarg.h>
#include <string.h>

#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

#ifdef DEBUG_PRINT
static int myPrint(const char* fmt, ...)
{
    va_list list;
    va_start(list, fmt);
    int r = vprintf(fmt, list);
    va_end(list);
    return r;
}
#else
static int myPrint(const char* fmt, ...)
{
    (void)fmt;
    return 0;
}
#endif

#define _GET_HEAD(H, ...) H

#define GET_HEAD(...) _GET_HEAD(__VA_ARGS__, 0)

#define GET_TAIL(H, ...) __VA_ARGS__

#define _PRINT(fmt, ...) myPrint("%s:%d:" fmt, __FILENAME__, __LINE__, __VA_ARGS__)

#define PRINT(...) _PRINT(GET_HEAD(__VA_ARGS__)"%.0d", GET_TAIL(__VA_ARGS__, 0))

#endif // __DEBUG_PRINT_H__
