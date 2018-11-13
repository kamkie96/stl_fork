#include <doubly_linked_list.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>


#define FREE(ptr) \
    do { \
      free(ptr); \
      ptr = NULL; \
    } while (0)


static nodeDoublyLinkedList_t*
createNode(const doublyLinkedList_t* const dll_p, const void* const inputData_p)
{
    assert(dll_p && inputData_p);

    nodeDoublyLinkedList_t* newNode_p = 
            (nodeDoublyLinkedList_t*)malloc(sizeof(*newNode_p));
    assert(newNode_p);

    newNode_p->__data_p__ = malloc(dll_p->__elementSize__);
    assert(newNode_p->__data_p__);
    
    newNode_p->__next_p__ = newNode_p->__prev_p__ = NULL;
    (void)memcpy(newNode_p->__data_p__, inputData_p, dll_p->__elementSize__);
    
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
init(const size_t element_size, int (*compare)(const void*, const void*))
{
    if ((element_size < 1) && !compare)
    {
        return NULL;
    }

    doublyLinkedList_t* newDoublyLinkedList_p =
            (doublyLinkedList_t*)malloc(sizeof(*newDoublyLinkedList_p));

    if (!newDoublyLinkedList_p)
    {
        return NULL;
    }

    newDoublyLinkedList_p->__size__ = 0;
    newDoublyLinkedList_p->__elementSize__ = element_size;
    newDoublyLinkedList_p->__compare__ = compare;
    newDoublyLinkedList_p->__head_p__ = newDoublyLinkedList_p->__tail_p__ = NULL;

    return newDoublyLinkedList_p;
}

int
clear(doublyLinkedList_t* dll_p)
{
    if (!dll_p)
    {
        return -1;
    }

    nodeDoublyLinkedList_t* currentNode_p = dll_p->__head_p__;
    nodeDoublyLinkedList_t* nextNode_p = NULL;

    while (currentNode_p != NULL)
    {
        nextNode_p = currentNode_p->__next_p__;
        freeNode(currentNode_p);
        currentNode_p = nextNode_p;
    }

    FREE(dll_p);
    return 0;
}

int
insert(doublyLinkedList_t* dll_p, const void* const inputData_p)
{
    if (!dll_p && !inputData_p)
    {
        return -1;
    }

    nodeDoublyLinkedList_t* newNode_p = createNode(dll_p, inputData_p);
    dll_p->__size__++;

    /* add first node */
    if (dll_p->__head_p__ == NULL)
    {
        dll_p->__head_p__ = dll_p->__tail_p__ = newNode_p;
        return 0;
    }

    /* add node to tail */
    if (dll_p->__compare__(newNode_p->__data_p__, dll_p->__tail_p__->__data_p__) >= 0)
    {
        nodeDoublyLinkedList_t* currentNode_p = dll_p->__tail_p__;
        currentNode_p->__next_p__ = newNode_p;
        newNode_p->__prev_p__ = currentNode_p;
        dll_p->__tail_p__ = newNode_p;
        return 0;
    }

    /* add node to head */
    if (dll_p->__compare__(newNode_p->__data_p__, dll_p->__head_p__->__data_p__) <= 0)
    {
        nodeDoublyLinkedList_t* currentNode_p = dll_p->__head_p__;
        currentNode_p->__prev_p__ = newNode_p;
        newNode_p->__next_p__ = currentNode_p;
        dll_p->__head_p__ = newNode_p;
        return 0;
    }
    
    /* add node between nodes */
    nodeDoublyLinkedList_t* currentNode_p = dll_p->__head_p__->__next_p__;

    while (currentNode_p != NULL)
    {
        if (dll_p->__compare__(newNode_p->__data_p__, currentNode_p->__data_p__) <= 0)
        {
            newNode_p->__next_p__ = currentNode_p;
            newNode_p->__prev_p__ = currentNode_p->__prev_p__;
            currentNode_p->__prev_p__->__next_p__ = newNode_p;
            currentNode_p->__prev_p__ = newNode_p;
            return 0;
        }
        currentNode_p = currentNode_p->__next_p__;
    }

    return -1;
}

int
erase(doublyLinkedList_t* dll_p, const void* const dataToDelete_p)
{
    if (!dll_p && !dataToDelete_p)
    {
        return -1;
    }

    if (size(dll_p) < 1)
    {
        return -1;
    }

    dll_p->__size__--;

    /* delete tail */
    if (dll_p->__compare__(dataToDelete_p, dll_p->__tail_p__->__data_p__) == 0)
    {
        /* situation when tail equals head */
        if (dll_p->__tail_p__ == dll_p->__head_p__)
        {
            freeNode(dll_p->__tail_p__);
            dll_p->__head_p__ = dll_p->__tail_p__ = NULL;
            return 0;
        }

        /* when tail is not last node in list */
        nodeDoublyLinkedList_t* tmpNodeToDelete_p = dll_p->__tail_p__;
        dll_p->__tail_p__ = dll_p->__tail_p__->__prev_p__;
        dll_p->__tail_p__->__next_p__ = NULL;
        freeNode(tmpNodeToDelete_p);
        return 0;
    }

    /* delete head */
    if (dll_p->__compare__(dataToDelete_p, dll_p->__head_p__->__data_p__) == 0)
    {
       nodeDoublyLinkedList_t* tmpNodeToDelete_p = dll_p->__head_p__;
       dll_p->__head_p__ = dll_p->__head_p__->__next_p__;
       dll_p->__head_p__->__prev_p__ = NULL;
       freeNode(tmpNodeToDelete_p);
       return 0;
    }

    /* delete between two node */
    nodeDoublyLinkedList_t* currentNode_p = dll_p->__head_p__->__next_p__;

    while (currentNode_p != dll_p->__tail_p__)
    {
        if (dll_p->__compare__(dataToDelete_p, currentNode_p->__data_p__) == 0)
        {
            nodeDoublyLinkedList_t* tmpNodeToDelete_p = currentNode_p;
            currentNode_p->__next_p__->__prev_p__ = currentNode_p->__prev_p__;
            currentNode_p->__prev_p__->__next_p__ = currentNode_p->__next_p__;
            freeNode(tmpNodeToDelete_p);
            return 0;
        }
    }

    return -1;
}

int
search(const doublyLinkedList_t* const dll_p, const void* const searchData_p)
{
    if (!dll_p && !searchData_p)
    {
        return -1;
    }

    if (size(dll_p) < 1)
    {
        return -1;
    }

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
    return (!dll_p) ? 0 : dll_p->__size__;
}

