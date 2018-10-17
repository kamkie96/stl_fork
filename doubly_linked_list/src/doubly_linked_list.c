#include <doubly_linked_list.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define FREE(ptr) \
    do { \
      free(ptr); \
      ptr = NULL; \
    } while (0)

static nodeDoublyLinkedList_t*
createNode(const doublyLinkedList_t* dll_p, void* data_p)
{
    assert(dll_p && data_p);
    nodeDoublyLinkedList_t *newNode_p = (nodeDoublyLinkedList_t*)malloc(sizeof(*newNode_p));
    newNode_p->__data_p__ = (void*)malloc(dll_p->__elementSize__);
    newNode_p->__next_p__ = newNode_p->__prev_p__ = NULL;
    memcpy(newNode_p->__data_p__, data_p, dll_p->__elementSize__);
    return newNode_p;
}

__attribute__((always_inline)) inline static void
freeNode(nodeDoublyLinkedList_t* node_p)
{
    assert(node_p);
    FREE(node_p->__data_p__);
    FREE(node_p);
}

doublyLinkedList_t*
init(size_t element_size, int (*compare)(const void*, const void*))
{
    assert((element_size > 0) && compare);

    doublyLinkedList_t* newDoublyLinkedList_p =
            (doublyLinkedList_t*)malloc(sizeof(*newDoublyLinkedList_p));
    newDoublyLinkedList_p->__size__ = 0;
    newDoublyLinkedList_p->__elementSize__ = element_size;
    newDoublyLinkedList_p->__compare__ = compare;
    newDoublyLinkedList_p->__head_p__ = newDoublyLinkedList_p->__tail_p__ = NULL;
    return newDoublyLinkedList_p;
}

void
clear(doublyLinkedList_t* dll_p)
{
    assert(dll_p);

    nodeDoublyLinkedList_t* currentNode_p = dll_p->__head_p__;
    nodeDoublyLinkedList_t* nextNode_p = NULL;

    while (currentNode_p != NULL)
    {
        nextNode_p = currentNode_p->__next_p__;
        freeNode(currentNode_p);
        currentNode_p = nextNode_p;
    }

    FREE(dll_p);
}

void
insert(doublyLinkedList_t* dll_p, void* data_p)
{
    assert(dll_p && data_p);

    nodeDoublyLinkedList_t* newNode_p = createNode(dll_p, data_p);
    dll_p->__size__++;

    if (dll_p->__head_p__ == NULL)
    {
        dll_p->__head_p__ = dll_p->__tail_p__ = newNode_p;
        return;
    }

    if (dll_p->__compare__(newNode_p->__data_p__, dll_p->__tail_p__->__data_p__) >= 0)
    {
        nodeDoublyLinkedList_t* currentNode_p = dll_p->__tail_p__;
        currentNode_p->__next_p__ = newNode_p;
        newNode_p->__prev_p__ = currentNode_p;
        dll_p->__tail_p__ = newNode_p;
        return;
    }

    if (dll_p->__compare__(newNode_p->__data_p__, dll_p->__head_p__->__data_p__) <= 0)
    {
        nodeDoublyLinkedList_t* currentNode_p = dll_p->__head_p__;
        currentNode_p->__prev_p__ = newNode_p;
        newNode_p->__next_p__ = currentNode_p;
        dll_p->__head_p__ = newNode_p;
        return;
    }
    
    nodeDoublyLinkedList_t* currentNode_p = dll_p->__head_p__->__next_p__;

    while (currentNode_p != NULL)
    {
        if (dll_p->__compare__(newNode_p->__data_p__, currentNode_p->__data_p__) <= 0)
        {
            newNode_p->__next_p__ = currentNode_p;
            newNode_p->__prev_p__ = currentNode_p->__prev_p__;
            currentNode_p->__prev_p__->__next_p__ = newNode_p;
            currentNode_p->__prev_p__ = newNode_p;
            return;
        }
        currentNode_p = currentNode_p->__next_p__;
    }
}

void
erase(doublyLinkedList_t* dll_p, void* outputData_p, size_t index)
{
    assert(dll_p && (size(dll_p) > index));

    nodeDoublyLinkedList_t* nodeToDelete = dll_p->__head_p__;
    for (size_t i = 0; i < index; i++)
    {
        nodeToDelete = nodeToDelete->__next_p__;
    }

    dll_p->__size__--;

    if (outputData_p)
    {
        memcpy(outputData_p, nodeToDelete->__data_p__, dll_p->__elementSize__);
    }

    if (nodeToDelete == dll_p->__head_p__ &&
        nodeToDelete == dll_p->__tail_p__)
    {
        freeNode(dll_p->__head_p__);
        dll_p->__head_p__ = dll_p->__tail_p__ = NULL;
        return;
    }

    if (nodeToDelete == dll_p->__head_p__)
    {
        dll_p->__head_p__ = dll_p->__head_p__->__next_p__;
        dll_p->__head_p__->__prev_p__ = NULL;
        freeNode(nodeToDelete);
        return;
    }

    if (nodeToDelete == dll_p->__tail_p__)
    {
        dll_p->__tail_p__ = dll_p->__tail_p__->__prev_p__;
        dll_p->__tail_p__->__next_p__ = NULL;
        freeNode(nodeToDelete);
        return;
    }

    nodeToDelete->__next_p__->__prev_p__ = nodeToDelete->__prev_p__;
    nodeToDelete->__prev_p__->__next_p__ = nodeToDelete->__next_p__;
    freeNode(nodeToDelete);
}

void
get(const doublyLinkedList_t* dll_p, void* outputData_p, size_t index)
{
    assert(dll_p && outputData_p && (size(dll_p) > index));

    nodeDoublyLinkedList_t* currentNode_p = dll_p->__head_p__;
    for (size_t i = 0; i < index; ++i)
    {
        currentNode_p = currentNode_p->__next_p__;
    }

    if (currentNode_p->__data_p__)
    {
        memcpy(outputData_p, currentNode_p->__data_p__, dll_p->__elementSize__);
    }
}

int
search(const doublyLinkedList_t* dll_p, void* searchData_p)
{
    assert(dll_p && searchData_p);

    nodeDoublyLinkedList_t* currentNode_p = dll_p->__head_p__;

    while (currentNode_p != NULL)
    {
        if (dll_p->__compare__(currentNode_p->__data_p__, searchData_p) == 0)
        {
            return 0;
        }
        currentNode_p = currentNode_p->__next_p__;
    }

    return -1;
}

size_t
size(const doublyLinkedList_t *dll_p)
{
    assert(dll_p);
    return dll_p->__size__;
}

