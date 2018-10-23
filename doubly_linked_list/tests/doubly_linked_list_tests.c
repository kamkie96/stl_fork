#include <doubly_linked_list.h>
#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <ctest.h>
#include <debug_print.h>

#define SIZE_OF_ARRAY(array) sizeof(array) / sizeof(array[0])

static int
compareInt32(const void* a, const void* b)
{
    assert(a && b);
    const int32_t* ia = (const int32_t*)a;
    const int32_t* ib = (const int32_t*)b;
    if (*ia > *ib) return 1;
    if (*ia == *ib) return 0;
    return -1;
}

static int
compareUint32(const void* a, const void* b)
{
    assert(a && b);
    const uint32_t* ia = (const uint32_t*)a;
    const uint32_t* ib = (const uint32_t*)b;
    if (*ia > *ib) return 1;
    if (*ia == *ib) return 0;
    return -1;
}

static int
compareDouble(const void* a, const void* b)
{
    assert(a && b);
    const double* ia = (const double*)a;
    const double* ib = (const double*)b;
    if (*ia > *ib) return 1;
    if (*ia == *ib) return 0;
    return -1;
}

static void
printInt32(const doublyLinkedList_t* dll_p)
{
    nodeDoublyLinkedList_t* currentNode_p = dll_p->__head_p__;

    while (currentNode_p != NULL)
    {
        printf("%d, ", *(int32_t*)currentNode_p->__data_p__);
        currentNode_p = currentNode_p->__next_p__;
    }
}

static void
printUint32(const doublyLinkedList_t* dll_p)
{
    nodeDoublyLinkedList_t* currentNode_p = dll_p->__head_p__;

    while (currentNode_p != NULL)
    {
        printf("%u, ", *(uint32_t*)currentNode_p->__data_p__);
        currentNode_p = currentNode_p->__next_p__;
    }
}


static void
printDouble(const doublyLinkedList_t* dll_p)
{
    nodeDoublyLinkedList_t* currentNode_p = dll_p->__head_p__;

    while (currentNode_p != NULL)
    {
        printf("%lf, ", *(double*)currentNode_p->__data_p__);
        currentNode_p = currentNode_p->__next_p__;
    }
}

/* ************************************************** */
/*                  TEST FUNCTIONS                    */
/* ************************************************** */

static void
testInitAndClearFuntions(void)
{
    doublyLinkedList_t* dll_p = init(sizeof(int32_t), compareInt32);
    NOT_EQUALS_PTR(dll_p, NULL);
//    NOT_EQUALS_PTR(dll_p->__head_p__)
    assert(dll_p);
    assert(dll_p->__head_p__ == NULL && dll_p->__tail_p__ == NULL);
    assert(dll_p->__compare__ == compareInt32);

    size_t size = 0;

    EQUALS_SIZE_T(dll_p->__size__, sizeof(int));
    EQUALS_SIZE_T(dll_p->__size__, size);
    EQUALS_INT(clear(dll_p), 0);
}

static void
testInsertFunction(void)
{
    printf("testInsertFunction\n");

    /* ************************************************** */
    /* test insert after tail */
    doublyLinkedList_t* dll_p = init(sizeof(int32_t), compareInt32);

    int32_t arrayOfInts[] = { 1, 2, 3, 4, 5 };

    for (size_t i = 0; i < SIZE_OF_ARRAY(arrayOfInts); i++)
    {
        insert(dll_p, &arrayOfInts[i]);
    }

    printInt32(dll_p);
    clear(dll_p);
    printf("\n");

    /* ************************************************** */
    /* test insert before head */

    dll_p = init(sizeof(int32_t), compareInt32);

    arrayOfInts[0] = 5;
    arrayOfInts[1] = 4;
    arrayOfInts[2] = 3;
    arrayOfInts[3] = 2;
    arrayOfInts[4] = 1;

    for (size_t i = 0; i < SIZE_OF_ARRAY(arrayOfInts); i++)
    {
        insert(dll_p, &arrayOfInts[i]);
    }

    printInt32(dll_p);
    clear(dll_p);
    printf("\n");

    /* ************************************************** */
    /* test insert in the middle of list */

    dll_p = init(sizeof(int32_t), compareInt32);

    arrayOfInts[0] = 1;
    arrayOfInts[1] = 5;
    arrayOfInts[2] = 2;
    arrayOfInts[3] = 3;
    arrayOfInts[4] = 4;

    for (size_t i = 0; i < SIZE_OF_ARRAY(arrayOfInts); i++)
    {
        insert(dll_p, &arrayOfInts[i]);
    }

    printInt32(dll_p);
    clear(dll_p);
    printf("\n");

    /* ************************************************** */
    /* test for many values */

    dll_p = init(sizeof(double), compareDouble);

    double arrayOfDoubles[] = { 3.14, 6.28, 8.56,
                                2.77, 2.09, 1.95,
                                5.78, 5.38, 5.89,
                                9.78, 9.98, 9.99,
                                0.45, 0.23, 0.11,
                                7.34, 5.85, 6.76 };

    for (size_t i = 0; i < SIZE_OF_ARRAY(arrayOfDoubles); i++)
    {
        insert(dll_p, &arrayOfDoubles[i]);
    }

    printDouble(dll_p);
    printf("\n");
    clear(dll_p);

    /* ************************************************** */
}

static void
testEraseFunction(void)
{
    printf("testEraseFunction\n");

    /* ************************************************** */
    /* delete node when head equals tail */
    doublyLinkedList_t* dll_p = init(sizeof(uint32_t), compareUint32);

    uint32_t testData = 10;

    insert(dll_p, &testData);

    printUint32(dll_p);
    printf("\n");

    assert(erase(dll_p, &testData) == 0);

    printUint32(dll_p);
    printf("\n");
    clear(dll_p);

    /* *************************************************** */
    /* erase value from tail, when tail is not equals head */

    dll_p = init(sizeof(uint32_t), compareUint32);

    uint32_t array[] = { 5, 10 };

    for (size_t i = 0; i < SIZE_OF_ARRAY(array); i++)
    {
        insert(dll_p, &array[i]);
    }

    printUint32(dll_p);
    printf("\n");

    assert(erase(dll_p, &array[1]) == 0);

    printUint32(dll_p);
    printf("\n");
    clear(dll_p);

    /* *************************************************** */
    /* erase value from head, when head is not equals head */

    dll_p = init(sizeof(uint32_t), compareUint32);

    uint32_t arrayForHead[] = { 5, 10 };

    for (size_t i = 0; i < SIZE_OF_ARRAY(arrayForHead); i++)
    {
        insert(dll_p, &arrayForHead[i]);
    }

    printUint32(dll_p);
    printf("\n");

    assert(erase(dll_p, &arrayForHead[0]) == 0);

    printUint32(dll_p);
    printf("\n");
    clear(dll_p);

    /* *************************************************** */
    /* erase value between two nodes */

    dll_p = init(sizeof(uint32_t), compareUint32);

    uint32_t arrayForMiddleNode[] = { 5, 10, 15 };

    for (size_t i = 0; i < SIZE_OF_ARRAY(arrayForMiddleNode); i++)
    {
        insert(dll_p, &arrayForMiddleNode[i]);
    }

    printUint32(dll_p);
    printf("\n");

    assert(erase(dll_p, &arrayForMiddleNode[1]) == 0);

    printUint32(dll_p);
    printf("\n");
    clear(dll_p);
}

int main(void)
{
    testInitAndClearFuntions();
    testInsertFunction();
    testEraseFunction();

    return 0;
}
