#include <stack.h>
#include <stdlib.h>
#include <assert.h>

#define FREE(ptr) \
    do { \
      free(ptr); \
      ptr = NULL; \
    } while (0)

int main(void)
{
    void* ptr = malloc(100);
    FREE(ptr);
    assert(ptr == NULL);
	return 0;
}
