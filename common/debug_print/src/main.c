#include <stdio.h>

#define DEBUG_PRINT
#include <debug_print.h>

int main(void)
{
    const int a = 5;
    PRINT("Hello world = %d\n", a);
    return 0;
}
