#include <stdio.h>
#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <stack.h>


#define SIZE_OF_ARRAY(array) sizeof(array) / sizeof(array[0])


static void
testInitAndClearFunctions(void)
{
    const size_t sizeStackOfUint32 = 10;
    stack_t* stack_p = init(sizeof(uint32_t), sizeStackOfUint32);
    assert(stack_p);
    assert(isEmpty(stack_p) == 0);
    assert(clear(stack_p) == 0);

    const size_t sizeStackOfDouble = 30;
    stack_p = init(sizeof(double), sizeStackOfDouble);
    assert(stack_p);
    assert(isEmpty(stack_p) == 0);
    assert(clear(stack_p) == 0);

    const size_t sizeStackOfCharArray = 20;
    stack_p = init(sizeof(char[10]), sizeStackOfCharArray);
    assert(stack_p);
    assert(isEmpty(stack_p) == 0);
    assert(clear(stack_p) == 0);
}

static void
testPushFunction(void)
{
    const size_t sizeStackOfInt32 = 5;
    stack_t* stack_p = init(sizeof(int32_t), sizeStackOfInt32);
    assert(stack_p);
    assert(isEmpty(stack_p) == 0);
    assert(isFull(stack_p) == -1);

    const int32_t arrayOfInt32[] =
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

    assert(stack_p->__capacity__ == sizeStackOfInt32);
    assert(isFull(stack_p) == 0);
    assert(isEmpty(stack_p) == -1);
    assert(clear(stack_p) == 0);

    /*******************************************************/

    const size_t sizeStackOfDouble = 10;
    stack_p = init(sizeof(double), sizeStackOfDouble);
    assert(stack_p);
    assert(isEmpty(stack_p) == 0);
    assert(isFull(stack_p) == -1);

    const double arrayOfDouble[] =
    {
      3.14, 6.28, 5.55, 13.25, 67.19,
      1.11, 7.23, 3.91, 39.99, 99.99
    };

    double expectedDouble = 0;

    for (size_t i = 0; i < SIZE_OF_ARRAY(arrayOfDouble); i++)
    {
        assert(push(stack_p, &arrayOfDouble[i]) == 0);
        assert(getTop(stack_p, &expectedDouble) == 0);
        assert(arrayOfDouble[i] == expectedDouble);
        printf("array[%zu] = %lf, expectedValue = %lf\n",
               i,
               arrayOfDouble[i],
               expectedDouble);
    }

    assert(stack_p->__capacity__ == sizeStackOfDouble);
    assert(isFull(stack_p) == 0);
    assert(isEmpty(stack_p) == -1);
    assert(clear(stack_p) == 0);
}

static void
testPopFunction(void)
{
    const size_t sizeStackOfUint16 = 5;
    stack_t* stack_p = init(sizeof(uint16_t), sizeStackOfUint16);
    assert(stack_p);
    assert(isEmpty(stack_p) == 0);
    assert(isFull(stack_p) == -1);

    const uint16_t arrayOfUint16[] =
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

    assert(stack_p->__capacity__ == sizeStackOfUint16);
    assert(isEmpty(stack_p) == -1);
    assert(isFull(stack_p) == 0);

    uint16_t expectedUint16TopValue = 0;
    uint16_t poppedUint16Value = 0;

    for (size_t i = 0; i < SIZE_OF_ARRAY(arrayOfUint16); i++)
    {
        assert(getTop(stack_p, &expectedUint16TopValue) == 0);
        assert(pop(stack_p, &poppedUint16Value) == 0);
        assert(expectedUint16TopValue == poppedUint16Value);
        printf("expectedUint16TopValue = %u, poppedUin16Value = %u\n",
               expectedUint16TopValue,
               poppedUint16Value);
    }

    assert(isEmpty(stack_p) == 0);
    assert(isFull(stack_p) == -1);
    assert(clear(stack_p) == 0);

    /*******************************************************/

    const size_t sizeStackOfDouble = 5;
    stack_p = init(sizeof(double), sizeStackOfDouble);
    assert(stack_p);
    assert(isEmpty(stack_p) == 0);
    assert(isFull(stack_p) == -1);

    const double arrayOfDouble[] =
    {
        3.14, 6.28, 9.42, 13.13, 73.73
    };

    double expectedDouble = 0;

    for (size_t i = 0; i < SIZE_OF_ARRAY(arrayOfDouble); i++)
    {
        assert(push(stack_p, &arrayOfDouble[i]) == 0);
        assert(getTop(stack_p, &expectedDouble) == 0);
        assert(arrayOfDouble[i] == expectedDouble);
        printf("array[%zu] = %lf, expectedValue = %lf\n",
               i,
               arrayOfDouble[i],
               expectedDouble);
    }

    assert(isEmpty(stack_p) == -1);
    assert(isFull(stack_p) == 0);
    assert(stack_p->__capacity__ == sizeStackOfDouble);

    double expectedDoubleTopValue = 0;
    double poppedDoubleValue = 0;

    for (size_t i = 0; i < SIZE_OF_ARRAY(arrayOfDouble); i++)
    {
        assert(getTop(stack_p, &expectedDoubleTopValue) == 0);
        assert(pop(stack_p, &poppedDoubleValue) == 0);
        assert(expectedDoubleTopValue == poppedDoubleValue);
        printf("expectedDoubleTopValue = %lf, poppedDoubleValue = %lf\n",
               expectedDoubleTopValue,
               poppedDoubleValue);
    }

    assert(isEmpty(stack_p) == 0);
    assert(isFull(stack_p) == -1);
    assert(clear(stack_p) == 0);
}

int 
main(void)
{
    testInitAndClearFunctions();
    testPushFunction();
    testPopFunction();
    
    return 0;
}
