#ifndef MM_H
#define MM_H

#define alloc_struct(name)	alloc_struct_(sizeof(struct name))

extern void *alloc_struct_(int);

#endif /* MM_H */
