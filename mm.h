#ifndef MM_H
#define MM_H

#define alloc_struct(name)	do_alloc_struct(sizeof(struct name))

extern void *do_alloc_struct(int);

#endif /* MM_H */
