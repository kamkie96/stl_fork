#include <stack.h>
#include <stdlib.h>
#include <string.h>

stack_t *init(size_t elementSize, size_t capacity)
{
    if (elementSize == 0 || capacity == 0)
    {
        return NULL;
    }

    stack_t* newStack_p = (stack_t*)malloc(sizeof(*newStack_p));

    if (!newStack_p)
    {
        return NULL;
    }

    newStack_p->__stackArray_p__ = malloc(elementSize * capacity);

    if (!newStack_p->__stackArray_p__)
    {
        free(newStack_p);
        return NULL;
    }

    newStack_p->__elementSize__ = elementSize;
    newStack_p->__capacity__ = capacity;
    newStack_p->__top__ = -1;
    return newStack_p;
}

int isFull(const stack_t* const stack_p)
{
    if (!stack_p)
    {
        return -1;
    }
    return stack_p->__top__ == stack_p->__capacity__ - 1 ? 0 : -1;
}

int isEmpty(const stack_t* const stack_p)
{
    if (!stack_p)
    {
        return -1;
    }
    return stack_p->__top__ == -1 ? 0 : -1;
}

int push(stack_t *stack_p, const void *dataToAdd_p)
{
    if (!stack_p || !dataToAdd_p)
    {
        return -1;
    }

    /* what if stack is full ? */

    stack_p->__top__++;
    void* destAddr_p = (char*)stack_p->__stackArray_p__ +
                       (stack_p->__top__ * stack_p->__elementSize__);
    (void)memcpy(destAddr_p, dataToAdd_p, stack_p->__elementSize__);
    return 0;
}

