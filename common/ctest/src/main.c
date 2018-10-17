#include <stdio.h>
#include <ctest.h>

static void
testForDoubles(void)
{
    double biggerValue = 999.999;
    double smallerValue = 0.00001;

    EQUALS_DOUBLE(biggerValue, biggerValue);
    NOT_EQUALS_DOUBLE(biggerValue, smallerValue);
    BIGGER_DOUBLE(biggerValue, smallerValue);
    SMALLER_DOUBLE(smallerValue, biggerValue);
}

static void
testForStrings(void)
{
    const char* longerString= "Hello";
    const char* shorterString= "C11";

    EQUALS_STRING(longerString, longerString);
    NOT_EQUALS_STRING(longerString, shorterString);
    BIGGER_STRING(longerString, shorterString);
    SMALLER_STRING(shorterString, longerString);
}

int main(void)
{
    BEGIN();
    TEST(testForDoubles());
    TEST(testForStrings());
    SUMMARY();

    return 0;
}
