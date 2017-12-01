#ifndef POOL_H
#define POOL_H

#include <stdlib.h>

#define KILO  1024
#define MEGA  (KILO * 1024)

#define alloc_struct(name)	alloc_from_default_pool(sizeof(struct name))

extern int   init_pool(size_t sz);
extern void  set_default_pool(int pool_id);
extern void *alloc_from_pool(int pool_id, size_t sz);
extern void *alloc_from_default_pool(size_t sz);
extern void  empty_pool(int pool_id);
extern void  release_pool(int pool_id);

#endif /* POOL_H */
