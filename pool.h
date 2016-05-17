#ifndef POOL_H
#define POOL_H

#include <stdbool.h>
#include <stdlib.h>

#define KILO  1024
#define MEGA  (KILO * 1024)

int   init_pool(size_t sz);
void *alloc_from_pool(int pool_id, size_t sz);
bool  empty_pool(int pool_id);
bool  release_pool(int pool_id);

#endif /* POOL_H */
