#ifndef __STACK_H__
#define __STACK_H__

#include <stddef.h>

typedef struct stack_t {
    void* __stackArray_p__;
    size_t __top__;
    size_t __capacity__;
    size_t __elementSize__;
} stack_t;

stack_t* init(const size_t elementSize, const size_t capacity);
int push(stack_t* stack_p, const void* inputData_p);
int pop(stack_t* stack_p, void* outputData_p);
int clear(stack_t* stack_p);
int getTop(const stack_t* const stack_p, void* outputData_p);
int isFull(const stack_t* const stack_p);
int isEmpty(const stack_t* const stack_p);

#endif /* __STACK_H__ */
