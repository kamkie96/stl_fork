#include <vector.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>


#define FREE(ptr) \
    do { \
        free(ptr); \
        ptr = NULL; \
    } while (0)


static int 
extend(vector_t* vector_p, const size_t ratio)
{
    void* tmpVectorArray_p = realloc(vector_p->__vectorArray_p__, vector_p->__capacity__ * ratio);

    if (!tmpVectorArray_p)
    {
        return -1;
    }

    vector_p->__vectorArray_p__ = tmpVectorArray_p;
    vector_p->__capacity__ *= ratio;

    return 0;
}


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
clear(vector_t* vector_p)
{
    if (!vector_p)
    {
        return -1;
    }

    FREE(vector_p->__vectorArray_p__);
    FREE(vector_p);
    return 0;
}


int 
insert(vector_t* vector_p, const void* inputData_p)
{
    if (!vector_p && !vector_p->__vectorArray_p__)
    {
        return -1;
    }    
    
    if (!inputData_p)
    {
        return -1;
    }       
    
    if (vector_p->__size__ == vector_p->__capacity__)
    {
        if (extend(vector_p, 2) == -1)
        {
            return -1;
        }
    }

    void* srcAddr_p = (char*)vector_p->__vectorArray_p__ +
                      (vector_p->__size__ * vector_p->__elementSize__);

    (void)memcpy(srcAddr_p, 
                 inputData_p, 
                 vector_p->__elementSize__);
    
    vector_p->__size__++;    
    return 0;
}


int 
delete(vector_t* vector_p, void* outputData_p)
{
    if (!vector_p && !vector_p->__vectorArray_p__)
    {
        return -1;
    }         
    
    const void* destAddr_p = (char*)vector_p->__vectorArray_p__ +
                             ((vector_p->__size__ - 1) * vector_p->__elementSize__);   

    if (outputData_p)
    {
        (void)memcpy(outputData_p, 
                     destAddr_p, 
                     vector_p->__elementSize__);
    }   
    
    vector_p->__size__--;    
    return 0;
}


int 
insert_pos(vector_t* vector_p, const size_t index, const void* inputData_p)
{
    if (!vector_p && !vector_p->__vectorArray_p__)
    {
        return -1;
    }    
    
    if (!inputData_p)
    {
        return -1;
    }    
    
    if (index > vector_p->__capacity__ - 1 &&
        index > vector_p->__size__)
    {
        return -1;
    }    
    
    if (vector_p->__size__ == vector_p->__capacity__)
    {
        if (extend(vector_p, 2) == -1)
        {
            return -1;
        }
    }      
   
    const void* srcAddr_p = (char*)vector_p->__vectorArray_p__ +
                            (index * vector_p->__elementSize__);
    void* destAddr_p = (char*)vector_p->__vectorArray_p__ +
                       ((index + 1) * vector_p->__elementSize__);    
                      
    (void)memmove(destAddr_p, 
                  srcAddr_p, 
                  vector_p->__elementSize__ * (vector_p->__size__ - index));
    
    (void)memcpy((void*)srcAddr_p, 
                 inputData_p, 
                 vector_p->__elementSize__);
    
    vector_p->__size__++;    
    return 0;
}


int 
delete_pos(vector_t* vector_p, const size_t index, void* outputData_p)
{
    if (!vector_p && !vector_p->__vectorArray_p__)
    {
        return -1;
    }    
   
    if (index > vector_p->__capacity__ - 1 &&
        index > vector_p->__size__)
    {
        return -1;
    }    

    if (index == vector_p->__size__)
    {
        if (narrow(vector_p, 2) == -1)
        {
            return -1;
        }
    }    
    
    const void* destAddr_p = (char*)vector_p->__vectorArray_p__ +
                             (index * vector_p->__elementSize__);
    void* srcAddr_p = (char*)vector_p->__vectorArray_p__ +
                      ((index + 1) * vector_p->__elementSize__);    

    if (outputData_p)
    {
        (void)memcpy(outputData_p, 
                     destAddr_p, 
                     vector_p->__elementSize__);
    }   
             
    (void)memmove((void*)destAddr_p, 
                  srcAddr_p, 
                  vector_p->__elementSize__ * (vector_p->__size__ - index));
    
    vector_p->__size__--;    
    return 0;
}