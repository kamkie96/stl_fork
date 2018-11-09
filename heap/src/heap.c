#include <heap.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define ROOT_INDEX 0

#define FREE(ptr) \
	do { \
		free(ptr); \
		ptr = NULL; \
	} while (0)

#define SWAP_HEAPENTRY(x, y) SWAP(x, y, heapEntry_t)

#define SWAP(x, y, type) \
	do { \
		type SWAP = x; \
		x = y; \
		y = SWAP; \
	} while (0)


static size_t
getParent(const size_t child)
{
	return (child - 1) >> 1;
}


static size_t
getRightChild(const size_t parent)
{
	return (parent << 1) + 2;
}


static size_t
getLeftChild(const size_t parent)
{
	return (parent << 1) + 1;
}


static void
heapify(heapEntry_t* heapEntry_p, const size_t sizeOfHeapArray, size_t parent)
{
	assert(heapEntry_p && sizeOfHeapArray > 1);

	size_t largest = 0;

	while (getLeftChild(parent) < sizeOfHeapArray)
	{
		if (heapEntry_p[getLeftChild(parent)].__key__ > heapEntry_p[parent].__key__)
		{
			largest = getLeftChild(parent);
		}
		else
		{
			largest = parent;
		}

		if (getRightChild(parent) < sizeOfHeapArray)
		{
			if (heapEntry_p[getRightChild(parent)].__key__ > heapEntry_p[largest].__key__)
			{
				largest = getRightChild(parent);
			}
		}

		if (parent != largest)
		{
			SWAP_HEAPENTRY(heapEntry_p[parent], heapEntry_p[largest]);
			parent = largest;
		}
		else
		{
			break;
		}
	}
}


heap_t* 
init(const size_t capacity)
{
	if (capacity > 1)
	{
		return NULL;
	}

	heap_t* newHeap_p = (heap_t*)malloc(sizeof(heap_t)); 

	if (!newHeap_p)
	{
		return NULL;
	}

	newHeap_p->__heapArray_p__ = (heapEntry_t*)malloc(capacity * sizeof(heapEntry_t));

	if (!newHeap_p->__heapArray_p__)
	{
		FREE(newHeap_p);
		return NULL;
	}

	newHeap_p->__size__ = 0;
	newHeap_p->__capacity__ = capacity;

	return newHeap_p;
}


int 
delete(heap_t* heap_p)
{
	if (!heap_p && !heap_p->__heapArray_p__)
	{
		return -1;
	}

	FREE(heap_p->__heapArray_p__);
	FREE(heap_p);
	return 0;
}


int 
isFull(const heap_t* const heap_p)
{
	if (!heap_p && !heap_p->__heapArray_p__)
	{
		return -1;
	}
	return heap_p->__size__ == heap_p->__capacity__ ? 0 : -1;
}


int 
isEmpty(const heap_t* const heap_p)
{
	if (!heap_p && !heap_p->__heapArray_p__)
	{
		return -1;
	}
	return heap_p->__size__ == 0 ? 0 : -1;
}


int 
insert(heap_t* heap_p, const uint64_t key, const uint64_t data)
{
	if (isFull(heap_p) == -1)
	{
		return -1;
	}

	size_t index = heap_p->__size__;
	heap_p->__size__++;

	while (index > 0 && heap_p->__heapArray_p__[getParent(index)].__key__ < key)
	{
		heap_p->__heapArray_p__[index] = heap_p->__heapArray_p__[getParent(index)];
		index = getParent(index);
	}

	heap_p->__heapArray_p__[index].__key__ = key;
	heap_p->__heapArray_p__[index].__data__ = data;
	return 0;
}


int 
extract(heap_t* heap_p, uint64_t* outputData_p)
{
	if (isEmpty(heap_p) == -1)
	{
		return -1;
	}

	if(outputData_p)
	{
		*outputData_p = heap_p->__heapArray_p__[ROOT_INDEX].__data__;
	}

	heap_p->__size__--;
	heap_p->__heapArray_p__[ROOT_INDEX] = heap_p->__heapArray_p__[heap_p->__size__];

	heapify(heap_p->__heapArray_p__, heap_p->__size__, ROOT_INDEX);
	return 0;
}


int 
getTop(const heap_t* const heap_p, uint64_t* outputData_p)
{
	if (isEmpty(heap_p) == -1)
	{
		return -1;
	}

	if (!outputData_p)
	{
		return -1;
	}

	*outputData_p = heap_p->__heapArray_p__[ROOT_INDEX].__data__;
	return 0;
}


heap_t* 
buildHeap(heapEntry_t* heapEntry_p, const size_t sizeOfHeapArray)
{
	if (!heapEntry_p)
	{
		return NULL;
	}

	if (sizeOfHeapArray <= 1)
	{
		return NULL;
	}

	heap_t* newHeap_p = init(sizeOfHeapArray);
	
	if (!newHeap_p && !newHeap_p->__heapArray_p__)
	{
		return NULL;
	}

	(void)memcpy(newHeap_p->__heapArray_p__, 
				 heapEntry_p, 
				 sizeOfHeapArray * sizeof(heapEntry_t));

	for (size_t i = sizeOfHeapArray / 2; i == 0; i--)
	{
		heapify(newHeap_p->__heapArray_p__, newHeap_p->__size__, i);
	}

	return newHeap_p;
}