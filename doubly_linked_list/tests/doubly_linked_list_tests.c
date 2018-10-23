#include <doubly_linked_list.h>
#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <ctest.h>

#define DEBUG_PRINT
#include <debug_print.h>

#define SIZE_OF_ARRAY(array) sizeof(array) / sizeof(array[0])

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

static void
printDouble(const doublyLinkedList_t* dll_p)
{
    nodeDoublyLinkedList_t* currentNode_p = dll_p->__head_p__;

    while (currentNode_p != NULL)
    {
        PRINT("%lf\n", *(double*)currentNode_p->__data_p__);
        currentNode_p = currentNode_p->__next_p__;
    }
}

static void
printUint32(const doublyLinkedList_t* dll_p)
{
    nodeDoublyLinkedList_t* currentNode_p = dll_p->__head_p__;

    while (currentNode_p != NULL)
    {
        PRINT("%u\n", *(uint32_t*)currentNode_p->__data_p__);
        currentNode_p = currentNode_p->__next_p__;
    }
}

/* ************************************************** */
/*                  TEST FUNCTIONS                    */
/* ************************************************** */

static void
testInitAndClearFuntions(void)
{
    doublyLinkedList_t* dll_p = init(sizeof(uint32_t), compareDouble);

    assert(dll_p);
    assert(dll_p->__head_p__ == NULL);
    assert(dll_p->__tail_p__ == NULL);
    assert(dll_p->__compare__ != NULL);
    assert(dll_p->__size__ == 0);
    assert(dll_p->__elementSize__ == sizeof(int32_t));
    assert(clear(dll_p) == 0);
}

static void
testInsertFunction(void)
{
    /* ************************************************** */
    /* test insert after tail */
    doublyLinkedList_t* dll_p = init(sizeof(uint32_t), compareUint32);

    uint32_t array[] = { 1, 2, 3, 4, 5 };

    for (size_t i = 0; i < SIZE_OF_ARRAY(array); i++)
    {
        assert(insert(dll_p, &array[i]) == 0);
    }

    printUint32(dll_p);
    assert(clear(dll_p) == 0);
    printf("\n");

    /* ************************************************** */
    /* test insert before head */

    dll_p = init(sizeof(uint32_t), compareUint32);

    array[0] = 5;
    array[1] = 4;
    array[2] = 3;
    array[3] = 2;
    array[4] = 1;

    for (size_t i = 0; i < SIZE_OF_ARRAY(array); i++)
    {
        assert(insert(dll_p, &array[i]) == 0);
    }

    printUint32(dll_p);
    assert(clear(dll_p) == 0);
    printf("\n");

    /* ************************************************** */
    /* test insert in the middle of list */

    dll_p = init(sizeof(double), compareDouble);

    double array2[] = { 1.453, 5.789, 2.238, 3.547, 4.443 };

    for (size_t i = 0; i < SIZE_OF_ARRAY(array2); i++)
    {
        assert(insert(dll_p, &array2[i]) == 0);
    }

    printDouble(dll_p);
    assert(clear(dll_p) == 0);
    printf("\n");
}

static void
testEraseFunction(void)
{
    /* ************************************************** */
    /* delete node when head equals tail */
    doublyLinkedList_t* dll_p = init(sizeof(double), compareDouble);

    double testData = 10;

    assert(insert(dll_p, &testData) == 0);

    printDouble(dll_p);
    printf("\n");

    assert(erase(dll_p, &testData) == 0);

    printDouble(dll_p);
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

    dll_p = init(sizeof(double), compareDouble);

    double arrayForHead[] = { 5.567, 10.002 };

    for (size_t i = 0; i < SIZE_OF_ARRAY(arrayForHead); i++)
    {
        assert(insert(dll_p, &arrayForHead[i]) == 0);
    }

    printDouble(dll_p);
    printf("\n");

    assert(erase(dll_p, &arrayForHead[0]) == 0);

    printDouble(dll_p);
    printf("\n");
    assert(clear(dll_p) == 0);

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

static void
testSearchFunction(void)
{
    doublyLinkedList_t* dll_p = init(sizeof(uint32_t), compareUint32);

    uint32_t array[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    for (size_t i = 0; i < SIZE_OF_ARRAY(array); i++)
    {
        assert(insert(dll_p, &array[i]) == 0);
    }

    /* *************************************************** */
    /* search head */

    assert(search(dll_p, &array[0]) == 0);

    /* *************************************************** */
    /* search tail */

    assert(search(dll_p, &array[SIZE_OF_ARRAY(array) - 1]) == 0);

    /* *************************************************** */
    /* search in middle of list */

    assert(search(dll_p, &array[SIZE_OF_ARRAY(array) / 2]) == 0);

    assert(clear(dll_p) == 0);
}

int main(void)
{
    testInitAndClearFuntions();
    testInsertFunction();
    testEraseFunction();
    testSearchFunction();
    return 0;
}
