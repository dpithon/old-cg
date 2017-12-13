#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include "log.h"
#include "macros.h"

#define ALIGNMENT			sizeof(void*)
#define is_ptr_aligned(ptr, alignment)	(((long int) ptr) % alignment == 0)
#define align(sz, alignment)		(((sz / alignment) + 1) * alignment)

struct pool {
	char *bottom;
	char *top;
	char *free;
};


static struct pool *pool;
static int *stack;

static int max_pools = 4;
static int top = -1;
static int initialized;


static void pool_first_init(void)
{
	stack = calloc(max_pools, sizeof(int));
	pool  = calloc(max_pools, sizeof(struct pool));

	if (stack == NULL || pool == NULL)
		fatal("pool_first_init: no memory left");

	for (int n = 0; n < max_pools; n++)
		stack[n] = n;

	top = max_pools;
	initialized = true;
}


void pool_set_max_pools(int max)
{
	assert(!initialized);
	assert(max > 0);

	max_pools = max;
}


/*
 * pool_init: allocate a new pool with given size
 *
 * sz: size of pool.
 *
 * returns pool_id or halt process
 */
int pool_init(size_t sz)
{
	int  pool_id;
	char *mem;

	if (!initialized)
		pool_first_init();

	if (!top)
		fatal("pool_init: no more pools");

	if (sz % ALIGNMENT) {
		warning("pool_init: force size alignment");	
		sz = align(sz, ALIGNMENT);
	}

	mem = malloc(sz);
	assert(is_ptr_aligned(mem, ALIGNMENT));

	if (mem == NULL)
		fatal("pool_init: failed to alloc memory");

	pool_id = stack[--top];
	pool[pool_id].top = mem + sz;
	pool[pool_id].bottom = pool[pool_id].free = mem;

	return pool_id;
}



void *pool_alloc(int pool_id, size_t sz)
{
	assert(initialized);
	assert(pool_id >= 0 && pool_id < max_pools);
	assert(pool[pool_id].bottom != NULL);

	char *mem = pool[pool_id].free;
	assert(is_ptr_aligned(mem, ALIGNMENT));

	if (mem + sz > pool[pool_id].top)
		fatal("pool overflow");

	if (sz % ALIGNMENT) {
		warning("pool_alloc: force alignment");	
		sz = align(sz, ALIGNMENT);
	}
	pool[pool_id].free += sz;

	return mem;
}


void pool_reset(int pool_id)
{
	assert(pool_id >= 0 && pool_id < max_pools);
	assert(pool[pool_id].bottom != NULL);

	pool[pool_id].free = pool[pool_id].bottom;
}


void pool_free(int pool_id)
{
	assert(pool_id >= 0 && pool_id < max_pools);
	assert(pool[pool_id].bottom != NULL);

	if (top >= max_pools)
		fatal("pool stack overflow");

	free(pool[pool_id].bottom);
	pool[pool_id].free = pool[pool_id].bottom = pool[pool_id].top = NULL;
	stack[top++] = pool_id;
}
