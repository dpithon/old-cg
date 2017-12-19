#ifndef POOL_PRIV_H
#define POOL_PRIV_H

#define ALIGNMENT			sizeof(void*)
#define is_ptr_aligned(ptr, alignment)	(((long int) ptr) % alignment == 0)
#define align(sz, alignment)		(((sz / alignment) + 1) * alignment)

#endif /* POOL_PRIV_H */
