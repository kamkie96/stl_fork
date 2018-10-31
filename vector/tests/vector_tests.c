#include <vector.h>
#include <assert.h>
#include <stdint.h>

static void
testInitAndClearFunctions(void)
{
    vector_t* vector_p = init(sizeof(uint32_t), 100);
    assert(vector_p);
    assert(clear(vector_p) == 0);
}

int main(void)
{
    testInitAndClearFunctions();
	return 0;
}
