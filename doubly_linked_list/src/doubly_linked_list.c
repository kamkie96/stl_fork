#include <doubly_linked_list.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#define free_ptr(ptr) \
    do { \
      void** _ptr = (ptr); \
      free(*(_ptr)); \
      *(_ptr) = NULL; \
    } while (0)

inline static node_doubly_linked_list_t*
create_node(const doubly_linked_list_t *dll_p, void *data_p)
{
    assert(dll_p && data_p);
    node_doubly_linked_list_t *newNode_p = (node_doubly_linked_list_t*)malloc(sizeof(*newNode_p));
    newNode_p->__data_p__ = malloc(sizeof(dll_p->__elementSize__));
    newNode_p->__next_p__ = newNode_p->__prev_p__ = NULL;
    memcpy(newNode_p->__data_p__, data_p, dll_p->__elementSize__);
    return newNode_p;
}

inline static void
free_node(node_doubly_linked_list_t* node_p)
{
    assert(node_p);
    free_ptr((void**)&node_p->__data_p__);
    free_ptr((void**)&node_p);
}

doubly_linked_list_t*
init(size_t element_size, int8_t (*compare)(const void*, const void*))
{
    assert(element_size > 0);
    assert(compare);

    doubly_linked_list_t* newDoublyLinkedList_p =
            (doubly_linked_list_t*)malloc(sizeof(doubly_linked_list_t));
    newDoublyLinkedList_p->__size__ = 0;
    newDoublyLinkedList_p->__elementSize__ = element_size;
    newDoublyLinkedList_p->__compare__ = compare;
    newDoublyLinkedList_p->__head_p__ = newDoublyLinkedList_p->__tail_p__ = NULL;
    return newDoublyLinkedList_p;
}

void
clear(doubly_linked_list_t *dll_p)
{
    assert(dll_p);

    node_doubly_linked_list_t *head_p = dll_p->__head_p__;
    node_doubly_linked_list_t *tmpHead_p = head_p;

    while (head_p != NULL)
    {
        tmpHead_p = head_p->__next_p__;
        free_node(head_p);
        head_p = tmpHead_p;
    }

    free_ptr((void**)&dll_p);
}

void
insert(doubly_linked_list_t* dll_p, void* data_p)
{
    assert(dll_p && data_p);
    node_doubly_linked_list_t* newNode_p = create_node(dll_p, data_p);

    dll_p->__size__++;

    if (dll_p->__head_p__ == NULL)
    {
        dll_p->__head_p__ = dll_p->__tail_p__ = newNode_p;
    }
    else
    {
        if (dll_p->__compare__(dll_p->__head_p__->__data_p__, newNode_p->__data_p__) == 1 ||
            dll_p->__compare__(dll_p->__head_p__->__data_p__, newNode_p->__data_p__) == 0)
        {
            node_doubly_linked_list_t* currentNode_p = dll_p->__head_p__;
            currentNode_p->__prev_p__ = newNode_p;
            newNode_p->__next_p__ = currentNode_p;
            dll_p->__head_p__ = newNode_p;
            return;
        }

        if (dll_p->__compare__(newNode_p->__data_p__, dll_p->__tail_p__->__data_p__) == 1 ||
            dll_p->__compare__(newNode_p->__data_p__, dll_p->__tail_p__->__data_p__) == 0)
        {
            node_doubly_linked_list_t* currentNode_p = dll_p->__tail_p__;
            currentNode_p->__next_p__ = newNode_p;
            newNode_p->__prev_p__ = currentNode_p;
            dll_p->__tail_p__ = newNode_p;
            return;
        }

        node_doubly_linked_list_t* currentNode_p = dll_p->__head_p__;

        while (currentNode_p->__next_p__ != NULL)
        {
            if (dll_p->__compare__(currentNode_p->__data_p__, newNode_p->__data_p__) == -1 &&
               (dll_p->__compare__(currentNode_p->__next_p__->__data_p__, newNode_p->__data_p__) == 1 ||
                dll_p->__compare__(currentNode_p->__next_p__->__data_p__, newNode_p->__data_p__) == 0))
            {
                break;
            }
            currentNode_p = currentNode_p->__next_p__;
        }

        newNode_p->__next_p__ = currentNode_p->__next_p__;
        newNode_p->__prev_p__ = currentNode_p->__next_p__->__prev_p__;
        currentNode_p->__next_p__->__prev_p__ = newNode_p;
        currentNode_p->__next_p__ = newNode_p;
    }
}

void
erase(doubly_linked_list_t *dll_p, void *outputData_p, size_t index)
{
    assert(dll_p);
    assert(dll_p->__size__ > index);

    node_doubly_linked_list_t *node_to_delete = dll_p->__head_p__;
    for (size_t i = 0; i < index; ++i)
    {
        node_to_delete = node_to_delete->__next_p__;
    }

    dll_p->__size__--;

    if (outputData_p)
        memcpy(outputData_p, node_to_delete->__data_p__, dll_p->__elementSize__);

    if (node_to_delete == dll_p->__head_p__ &&
        node_to_delete == dll_p->__tail_p__)
    {
        free_node(dll_p->__head_p__);
        dll_p->__head_p__ = dll_p->__tail_p__ = NULL;
        return;
    }

    if (node_to_delete == dll_p->__head_p__)
    {
        dll_p->__head_p__ = dll_p->__head_p__->__next_p__;
        dll_p->__head_p__->__prev_p__ = NULL;
        free_node(node_to_delete);
        return;
    }

    if (node_to_delete == dll_p->__tail_p__)
    {
        dll_p->__tail_p__ = dll_p->__tail_p__->__prev_p__;
        dll_p->__tail_p__->__next_p__ = NULL;
        free_node(node_to_delete);
        return;
    }

    node_to_delete->__next_p__->__prev_p__ = node_to_delete->__prev_p__;
    node_to_delete->__prev_p__->__next_p__ = node_to_delete->__next_p__;
    free_node(node_to_delete);
}

void
get(const doubly_linked_list_t *dll_p, void *output_data_p, size_t index)
{
    assert(dll_p && output_data_p);
    assert(size(dll_p) > index);

    node_doubly_linked_list_t* currentNode_p = dll_p->__head_p__;
    for (size_t i = 0; i < index; ++i)
    {
        currentNode_p = currentNode_p->__next_p__;
    }

    if (currentNode_p->__data_p__)
        memcpy(output_data_p, currentNode_p->__data_p__, dll_p->__elementSize__);
}

int
search(const doubly_linked_list_t *dll_p, void* searchData_p)
{
    assert(dll_p && searchData_p);

    node_doubly_linked_list_t* currentNode_p = dll_p->__head_p__;

    while (currentNode_p != NULL)
    {
        if (dll_p->__compare__(currentNode_p->__data_p__, searchData_p) == 0)
            return 0;

        currentNode_p = currentNode_p->__next_p__;
    }

    return -1;
}

size_t
size(const doubly_linked_list_t *dll_p)
{
    assert(dll_p);
    return dll_p->__size__;
}

