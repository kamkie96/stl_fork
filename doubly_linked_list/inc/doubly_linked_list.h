#ifndef __DOUBLY_LINKED_LIST_H__
#define __DOUBLY_LINKED_LIST_H__

#include <stddef.h>
#include <stdint.h>

typedef struct node_doubly_linked_list_t
{
    void* __data_p__;
    struct node_doubly_linked_list_t* __next_p__;
    struct node_doubly_linked_list_t* __prev_p__;
} node_doubly_linked_list_t;

typedef struct doubly_linked_list_t
{
    size_t __elementSize__;
    size_t __size__;
    node_doubly_linked_list_t* __head_p__;
    node_doubly_linked_list_t* __tail_p__;
    int8_t (*__compare__)(const void* a, const void* b);
} doubly_linked_list_t;

doubly_linked_list_t* init(size_t element_size, int8_t (*compare)(const void*, const void*));
void insert(doubly_linked_list_t* dll_p, void* data_p);
void erase(doubly_linked_list_t* dll_p, void* outputData_p, size_t index);
void get(const doubly_linked_list_t* dll_p, void* outputData_p, size_t index);
int search(const doubly_linked_list_t* dll_p, void* searchData_p);
void clear(doubly_linked_list_t* dll_p);
size_t size(const doubly_linked_list_t* dll_p);

#endif // __DOUBLY_LINKED_LIST_H__
