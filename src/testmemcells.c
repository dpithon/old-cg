#include <stdio.h>
#include "memcells.h"
#include "pool.h"

struct thing  {
	int a;
	char b;
};

int main()
{
	struct pool pool;
	struct memcells memcells;
	struct thing *a[128];

	pool_init(&pool, 2 * KILO);
	memcells_init(&memcells, &pool, 128, sizeof(struct thing));

	for (int i = 0; i < 128; i++)
		a[i] = memcells_lease(&memcells);

	for (int i = 0; i < 128; i++)
		memcells_release(&memcells, a[i]);

	return 0;
}
