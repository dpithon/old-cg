#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include "log.h"

#define MAX_POOL	16

static int default_pool = -1;

static struct pool {
	char *bottom;
	char *top;
	char *free;
} pool[MAX_POOL];

static int stack[MAX_POOL];
static int top = -1;
static int initialized;


static void init_stack(void)
{
	for (int n = 0; n < MAX_POOL; n++)
		stack[n] = n;

	top = MAX_POOL;
	initialized = true;
}


/*
 * init_new_pool: allocate a new pool with given size
 *
 * sz: size of pool.
 *
 * returns pool id or raise fatal error
 */
int init_new_pool(size_t sz)
{
	int  pool_id;
	char *mem;

	if (!initialized)
		init_stack();

	if (!top)
		fatal("no more pool on stack");

	if ((mem = malloc(sz)) == NULL)
		fatal("out of memory");

	pool_id = stack[--top];
	pool[pool_id].bottom = pool[pool_id].free = mem;
	pool[pool_id].top = mem + sz;

	return pool_id;
}


void set_default_pool(int pool_id)
{
	assert(pool_id >= 0 && pool_id < MAX_POOL);
	assert(pool[pool_id].bottom != NULL);

	default_pool = pool_id;
}


void *alloc_from_pool(int pool_id, size_t sz)
{
	assert(pool_id >= 0 && pool_id < MAX_POOL);
	assert(pool[pool_id].bottom != NULL);

	char *mem = pool[pool_id].free;
	if (mem + sz > pool[pool_id].top)
		fatal("pool overflow");

	pool[pool_id].free += sz;

	return mem;
}


void *alloc_from_default_pool(size_t sz)
{
	return alloc_from_pool(default_pool, sz);
}


void empty_pool(int pool_id)
{
	assert(pool_id >= 0 && pool_id < MAX_POOL);
	assert(pool[pool_id].bottom != NULL);

	if (pool[pool_id].free == pool[pool_id].bottom)
		warning("pool already empty");

	pool[pool_id].free = pool[pool_id].bottom;
}


void release_pool(int pool_id)
{
	assert(pool_id >= 0 && pool_id < MAX_POOL);
	assert(pool[pool_id].bottom != NULL);

	if (top >= MAX_POOL)
		fatal("pool stack overflow");

	free(pool[pool_id].bottom);
	pool[pool_id].free = pool[pool_id].bottom = pool[pool_id].top = NULL;
	stack[top++] = pool_id;
}
