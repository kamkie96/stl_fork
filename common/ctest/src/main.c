#include <stdio.h>
#include <ctest.h>

static void
testForInts(void)
{
    int biggerValue = 10000;
    int smallerValue = 0;

    ASSERT_INT(biggerValue, biggerValue);
    ASSERT_INT(biggerValue, smallerValue);
}

static void
testForSizet(void)
{
    size_t biggerValue = 10000;
    size_t smallerValue = 0;

    ASSERT_SIZE_T(biggerValue, biggerValue);
    ASSERT_SIZE_T(biggerValue, smallerValue);
}

static void
testForStrings(void)
{
    const char* longerString= "Hello world";
    const char* shorterString= "C11";

    ASSERT_STR(longerString, longerString);
    ASSERT_STR(longerString, shorterString);
    EXPECT_SIZE_T(11, strlen(longerString));
    EXPECT_SIZE_T(3, strlen(shorterString));
}

static void
testForPointers(void)
{
    int a = 5;
    int b = 10;

    void* ptr1 = &a;
    void* ptr2 = &b;

    ASSERT_PTR(ptr1, ptr1);
    ASSERT_PTR(ptr1, ptr2);
}

int
main(void)
{
    BEGIN();
    TEST(testForInts());
    TEST(testForSizet());
    TEST(testForStrings());
    TEST(testForPointers());
    SUMMARY();

    return 0;
}
