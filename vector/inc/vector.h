#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <stddef.h>

typedef struct vector_t {
    size_t __size__;
    size_t __capacity__;
    size_t __elementSize__;
    void* __vectorArray_p__;
} vector_t;

vector_t* init(const size_t elementSize, const size_t capacity);
int clear(vector_t* vector_p);
int set(vector_t* vector_p, const size_t index, const void* inputData_p);
int get(vector_t* vector_p, const size_t index, void* outputData_p);

#endif /* __VECTOR_H__ */
