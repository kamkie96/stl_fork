#include <stack.h>
#include <stdlib.h>
#include <string.h>

#define FREE(ptr) \
    do { \
      free(ptr); \
      ptr = NULL; \
    } while (0)

stack_t*
init(const size_t elementSize, const size_t capacity)
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
        FREE(newStack_p);
        return NULL;
    }

    newStack_p->__elementSize__ = elementSize;
    newStack_p->__capacity__ = capacity;
    newStack_p->__top__ = -1;
    return newStack_p;
}

int
clear(stack_t *stack_p)
{
    if (!stack_p)
    {
        return -1;
    }

    FREE(stack_p->__stackArray_p__);
    FREE(stack_p);
    return 0;
}

int
isFull(const stack_t* const stack_p)
{
    if (!stack_p)
    {
        return -1;
    }
    return stack_p->__top__ == stack_p->__capacity__ - 1 ? 0 : -1;
}

int
isEmpty(const stack_t* const stack_p)
{
    if (!stack_p)
    {
        return -1;
    }
    return stack_p->__top__ == -1 ? 0 : -1;
}

int
getTop(const stack_t* const stack_p, void* outputData_p)
{
    if (!stack_p)
    {
        return -1;
    }

    if (isEmpty(stack_p))
    {
        return -1;
    }

    const void* sourceAddr_p = (char*)stack_p->__stackArray_p__ +
                               ((size_t)stack_p->__top__ * stack_p->__elementSize__);
    (void)memcpy(outputData_p, sourceAddr_p, stack_p->__elementSize__);
    return 0;
}

int
push(stack_t* stack_p, const void* inputData_p)
{
    if (!stack_p && !inputData_p)
    {
        return -1;
    }

    if (isFull(stack_p) != 0)
    {
        return -1;
    }

    stack_p->__top__++;
    void* destAddr_p = (char*)stack_p->__stackArray_p__ +
                       ((size_t)stack_p->__top__ * stack_p->__elementSize__);
    (void)memcpy(destAddr_p, inputData_p, stack_p->__elementSize__);
    return 0;
}

int
pop(stack_t *stack_p, void *outputData_p)
{
    if (!stack_p)
    {
        return -1;
    }

    if (isEmpty(stack_p) == 0)
    {
        return -1;
    }

    if (outputData_p)
    {
        const void* sourceAddr_p = (char*)stack_p->__stackArray_p__ +
                                   ((size_t)stack_p->__top__ * stack_p->__elementSize__);
        (void)memcpy(outputData_p, sourceAddr_p, stack_p->__elementSize__);
    }

    stack_p->__top__--;
    return 0;
}
