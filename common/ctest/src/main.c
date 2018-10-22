#include <stdio.h>
#include <ctest.h>

static void
testForInts(void)
{
    int biggerValue = 10000;
    int smallerValue = 0;

    EQUALS_INT(biggerValue, biggerValue);
    NOT_EQUALS_INT(biggerValue, smallerValue);
    BIGGER_INT(biggerValue, smallerValue);
    SMALLER_INT(smallerValue, biggerValue);
}

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
    const char* longerString= "Hello world";
    const char* shorterString= "C11";

    EQUALS_STRING(longerString, longerString);
    NOT_EQUALS_STRING(longerString, shorterString);
    LONGER_STRING(longerString, shorterString);
    SHORTER_STRING(shorterString, longerString);
}

static void
testForPointers(void)
{
    char string[] = "Hello world!";
    int value = 2;

    void* ptr1 = &string[0];
    void* ptr2 = &value;

    EQUALS_PTR(ptr1, ptr1);
    NOT_EQUALS_PTR(ptr1, ptr2);
}

int
main(void)
{
    BEGIN();
    TEST(testForInts());
    TEST(testForDoubles());
    TEST(testForStrings());
    TEST(testForPointers());
    SUMMARY();

    return 0;
}
