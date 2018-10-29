#ifndef __STACK_H__
#define __STACK_H__

#include <stddef.h>
#include <stdint.h>

typedef struct stack_t {
    void* __stackArray_p__;
    int32_t __top__;
    size_t __capacity__;
    size_t __elementSize__;
} stack_t;

stack_t* init(size_t elementSize, size_t capacity);
int push(stack_t* stack_p, const void* dataToAdd_p);
int isFull(const stack_t* const stack_p);
int isEmpty(const stack_t* const stack_p);
/* enable to expand stack double times.
   question is, how to write it well ? */
int expandStack(stack_t* stack_p);

#endif /* __STACK_H__ */
