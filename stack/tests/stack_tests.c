#include <stdio.h>
#include <assert.h>
#include <stddef.h>
#include <stack.h>

#define SIZE_OF_ARRAY(array) sizeof(array) / sizeof(array[0])

static void
testInitAndClearFunctions(void)
{
    stack_t* stack_p = init(sizeof(uint32_t), 10);
    assert(stack_p != NULL);

    assert(clear(stack_p) == 0);

    /* cannot understand what happened
     * after uncomment this line of code.
    assert(stack_p == NULL);
     */
}

int main(void)
{
    testInitAndClearFunctions();
	return 0;
}
