#ifndef __HEAP_H__
#define __HEAP_H__


#include <stdint.h>
#include <stddef.h>


typedef struct heapEntry_t {
    uint64_t __key__;
    uint64_t __data__;
} heapEntry_t;


typedef struct heap_t {
    size_t __size__;
    size_t __capacity__;
    heapEntry_t* __heapArray_p__;
} heap_t;


heap_t* init(const size_t capacity);
int delete(heap_t* heap_p);
int isFull(const heap_t* const heap_p);
int isEmpty(const heap_t* const heap_p);
int insert(heap_t* heap_p, const uint64_t key, const uint64_t data);
int extract(heap_t* heap_p, uint64_t* outputData_p);
int getTop(const heap_t* const heap_p, uint64_t* outputData_p);
heap_t* buildHeap(heapEntry_t* heapEntry_p, const size_t sizeOfHeapArray);


#endif /* __HEAP_H__ */
