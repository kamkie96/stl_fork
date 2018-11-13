#ifndef __DOUBLY_LINKED_LIST_H__
#define __DOUBLY_LINKED_LIST_H__


#include <stddef.h>


typedef struct nodeDoublyLinkedList_t
{
    void* __data_p__;
    struct nodeDoublyLinkedList_t* __next_p__;
    struct nodeDoublyLinkedList_t* __prev_p__;
} nodeDoublyLinkedList_t;


typedef struct doublyLinkedList_t
{
    size_t __elementSize__;
    size_t __size__;
    nodeDoublyLinkedList_t* __head_p__;
    nodeDoublyLinkedList_t* __tail_p__;
    int (*__compare__)(const void*, const void*);
} doublyLinkedList_t;


doublyLinkedList_t* init(const size_t elementSize, int (*compare)(const void*, const void*));
int insert(doublyLinkedList_t* dll_p, const void* const inputData_p);
int erase(doublyLinkedList_t* dll_p, const void* const dataToDelete_p);
int search(const doublyLinkedList_t* const dll_p, const void* const searchData_p);
int clear(doublyLinkedList_t* dll_p);
size_t size(const doublyLinkedList_t* const dll_p);

#endif // __DOUBLY_LINKED_LIST_H__
