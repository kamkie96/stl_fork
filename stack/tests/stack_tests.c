#include <stdio.h>
#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <stack.h>

#define SIZE_OF_ARRAY(array) sizeof(array) / sizeof(array[0])

static void
testInitAndClearFunctions(void)
{
    stack_t* stack_p = init(sizeof(uint32_t), 10);
    assert(stack_p);
    assert(clear(stack_p) == 0);

    stack_p = init(sizeof(double), 30);
    assert(stack_p);
    assert(clear(stack_p) == 0);

    stack_p = init(sizeof(char[20]), 15);
    assert(stack_p);
    assert(clear(stack_p) == 0);
}

static void
testPushFunction(void)
{
    stack_t* stack_p = init(sizeof(int32_t), 5);
    assert(stack_p);

    int32_t arrayOfInt32[] =
    {
      2, 3, 5, 7, 11
    };

    int32_t expectedInt32 = 0;

    for (size_t i = 0; i < SIZE_OF_ARRAY(arrayOfInt32); i++)
    {
        assert(push(stack_p, &arrayOfInt32[i]) == 0);
        assert(getTop(stack_p, &expectedInt32) == 0);
        assert(arrayOfInt32[i] == expectedInt32);
        printf("array[%zu] = %d, expectedValue = %d\n",
               i,
               arrayOfInt32[i],
               expectedInt32);
    }

    assert(clear(stack_p) == 0);

    /*******************************************************/

    stack_p = init(sizeof(double), 10);
    assert(stack_p);

    double arrayOfDouble[] =
    {
      3.14, 6.28, 5.55, 13.25, 67.19,
      1.11, 7.23, 3.91, 39.99, 99.99
    };

    double expectedDouble = 0;

    for (size_t i = 0; i < SIZE_OF_ARRAY(arrayOfInt32); i++)
    {
        assert(push(stack_p, &arrayOfDouble[i]) == 0);
        assert(getTop(stack_p, &expectedDouble) == 0);
        assert(arrayOfDouble[i] == expectedDouble);
        printf("array[%zu] = %lf, expectedValue = %lf\n",
               i,
               arrayOfDouble[i],
               expectedDouble);
    }

    assert(clear(stack_p) == 0);
}

static void
testPopFunction(void)
{
    stack_t* stack_p = init(sizeof(uint16_t), 5);
    assert(stack_p);

    uint16_t arrayOfUint16[] =
    {
        115, 117, 119, 123, 133
    };

    uint16_t expectedUint16 = 0;

    for (size_t i = 0; i < SIZE_OF_ARRAY(arrayOfUint16); i++)
    {
        assert(push(stack_p, &arrayOfUint16[i]) == 0);
        assert(getTop(stack_p, &expectedUint16) == 0);
        assert(arrayOfUint16[i] == expectedUint16);
        printf("array[%zu] = %u, expectedValue = %u\n",
               i,
               arrayOfUint16[i],
               expectedUint16);
    }

    uint16_t expectedTopValue = 0;
    uint16_t poppedValue = 0;

    for (size_t i = 0; i < SIZE_OF_ARRAY(arrayOfUint16); i++)
    {
        assert(getTop(stack_p, &expectedTopValue) == 0);
        assert(pop(stack_p, &poppedValue) == 0);
        assert(expectedTopValue == poppedValue);
        printf("expectedTopValue = %u, popedValue = %u\n",
               expectedTopValue,
               poppedValue);
    }

    assert(clear(stack_p) == 0);
}

int main(void)
{
    testInitAndClearFunctions();
    testPushFunction();
    testPopFunction();
    return 0;
}
