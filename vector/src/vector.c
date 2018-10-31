#include <vector.h>
#include <stdlib.h>
#include <assert.h>

#define FREE(ptr) \
    do { \
        free(ptr); \
        ptr = NULL; \
    } while (0)

#if 0
static void
reserve(vector_t* vector_p)
{
    return;
}
#endif

vector_t*
init(const size_t elementSize, const size_t capacity)
{
    if (elementSize == 0 || capacity == 0)
    {
        return NULL;
    }

    vector_t* vector_p = (vector_t*)malloc(sizeof(*vector_p));

    if (!vector_p)
    {
        return NULL;
    }

    vector_p->__vectorArray_p__ = malloc(elementSize * capacity);

    if (!vector_p->__vectorArray_p__)
    {
        FREE(vector_p);
        return NULL;
    }

    vector_p->__size__ = 0;
    vector_p->__capacity__ = capacity;
    vector_p->__elementSize__ = elementSize;
    return vector_p;
}

int
clear(vector_t *vector_p)
{
    if (!vector_p)
    {
        return -1;
    }

    FREE(vector_p->__vectorArray_p__);
    FREE(vector_p);
    return 0;
}
