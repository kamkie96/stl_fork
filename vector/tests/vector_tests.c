#include <vector.h>
#include <assert.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>


#define SIZE_OF_ARRAY(array) sizeof(array) / sizeof(array[0])


static void 
printVectorOfUint32(const vector_t* const vector_p)
{
	uint32_t* vectorArray = (uint32_t*)vector_p->__vectorArray_p__;
	for (size_t i = 0; i < vector_p->__capacity__; i++)
	{
		printf("%u ", vectorArray[i]);
	}
	printf("\n");
}


static void
testInitAndClearFunctions(void)
{
	const size_t elementSize = sizeof(uint32_t);
	const size_t capacity = 10;

	vector_t* vector_p = init(elementSize, capacity);
	assert(vector_p);

	assert(clear(vector_p) == 0);
}


static void
testInsertFunction(void)
{
	const size_t elementSize = sizeof(uint32_t);
	const size_t capacity = 8;

	vector_t* vector_p = init(elementSize, capacity);
	assert(vector_p);

	const uint32_t arrayOfUint32[] =
	{
		2, 3, 5, 7, 11, 13, 17, 19
	};

	for (size_t i = 0; i < SIZE_OF_ARRAY(arrayOfUint32); i++)
	{
		assert(insert(vector_p, &arrayOfUint32[i]) == 0);
	}

	assert(vector_p->__size__ == SIZE_OF_ARRAY(arrayOfUint32));

	printVectorOfUint32(vector_p);

	assert(clear(vector_p) == 0);
}

static void 
testDeleteFunction(void)
{
	const size_t elementSize = sizeof(uint32_t);
	const size_t capacity = 8;

	vector_t* vector_p = init(elementSize, capacity);
	assert(vector_p);

	const uint32_t arrayOfUint32[] =
	{
		0, 1, 1, 2, 3, 5, 8, 13
	};

	for (size_t i = 0; i < SIZE_OF_ARRAY(arrayOfUint32); i++)
	{
		assert(insert(vector_p, &arrayOfUint32[i]) == 0);
	}

	assert(vector_p->__size__ == SIZE_OF_ARRAY(arrayOfUint32));
	printVectorOfUint32(vector_p);

	for (size_t i = 0; i < SIZE_OF_ARRAY(arrayOfUint32); i++)
	{
		uint32_t outputData = 0;
		assert(delete(vector_p, &outputData) == 0);
		printf("%u ", outputData);
	}

	assert(vector_p->__size__ == 0);
	assert(clear(vector_p) == 0);
}


int main(void)
{
	testInitAndClearFunctions();
	testInsertFunction();
	testDeleteFunction();
	return 0;
}
