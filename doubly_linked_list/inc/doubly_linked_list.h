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
void insert(doublyLinkedList_t* dll_p, void* data_p);
void erase(doublyLinkedList_t* dll_p, void* outputData_p, size_t index);
void get(const doublyLinkedList_t* dll_p, void* outputData_p, size_t index);
int search(const doublyLinkedList_t* dll_p, void* searchData_p);
void clear(doublyLinkedList_t* dll_p);
size_t size(const doublyLinkedList_t* dll_p);

#endif // __DOUBLY_LINKED_LIST_H__
