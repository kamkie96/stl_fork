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
    int (*__compare__)(const void* a, const void* b);
} doublyLinkedList_t;

doublyLinkedList_t* init(size_t elementSize, int (*compare)(const void*, const void*));
int insert(doublyLinkedList_t* dll_p, const void* data_p);
int erase(doublyLinkedList_t* dll_p, const void* nodeToDelete_p);
int search(const doublyLinkedList_t* dll_p, const void* searchData_p);
int clear(doublyLinkedList_t* dll_p);
size_t size(const doublyLinkedList_t* dll_p);

#endif // __DOUBLY_LINKED_LIST_H__
