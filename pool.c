#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include "log.h"

#define MAX_POOL	16

static struct pool {
	char *bottom;
	char *top;
	char *free;
} pool[MAX_POOL];

static int stack[MAX_POOL];
static int top = -1;
static int initialized;


/*
 * init_pool: allocate a new pool with given size
 *
 * sz: size of pool
 *
 * returns pool id or raise fatal error
 */
int init_pool(size_t sz)
{
	if (!initialized) {
		for (int n = 0; n < MAX_POOL; n++)
			stack[n] = n;

		top = MAX_POOL;
		initialized = true;
	}

	if (top) {
		int pool_id = stack[--top];
		char *mem = malloc(sz);
		if (mem == NULL)
			fatal("out of memory");
		pool[pool_id].bottom = pool[pool_id].free = mem;
		pool[pool_id].top = mem + sz;
		return pool_id;
	}

	fatal("no more pool");
	return -1; /* never reached */
}


char *alloc_from_pool(int pool_id, size_t sz)
{
	assert(pool[pool_id].bottom != NULL);

	char *mem = pool[pool_id].free;
	if (mem + sz > pool[pool_id].top)
		fatal("pool overflow");

	pool[pool_id].free += sz;

	return mem;
}


void empty_pool(int pool_id)
{
	assert(pool[pool_id].bottom != NULL);
	pool[pool_id].free = pool[pool_id].bottom;
}


void release_pool(int pool_id)
{
	assert(top < MAX_POOL);
	assert(pool[pool_id].bottom != NULL);

	free(pool[pool_id].bottom);
	pool[pool_id].free = pool[pool_id].bottom = pool[pool_id].top = NULL;
	stack[top++] = pool_id;
}
