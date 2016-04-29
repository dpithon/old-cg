#include <assert.h>
#include <stdlib.h>

#include "log.h"

void *alloc_struct_(int sz)
{
	assert(sz > 0);

	void *ptr = malloc(sz);
	if (!ptr)
		fatal("failed to allocate memory");

	return ptr;
}
