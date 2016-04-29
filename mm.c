#include <assert.h>
#include <stdlib.h>

#include "log.h"

void *do_alloc_struct(int sz)
{
	assert(sz > 0);

	void *ptr = malloc(sz);
	if (!ptr)
		fatal("failed to allocate memory");

	return ptr;
}



