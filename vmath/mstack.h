#ifndef _VMATH_MSTACK_H
#define _VMATH_MSTACK_H

/* Matrix stack */
#define MAX_STACK_SIZE	16
typedef struct mstack {
	matrix_t m[MAX_STACK_SIZE];
	int i;
} mstack_t;

extern void stack_init_r(mstack_t*);
extern bool stack_push_r(mstack_t*, const matrix_t*);
extern bool stack_pop_r(mstack_t*);
extern const matrix_t *stack_peek_r(mstack_t*);

extern bool stack_push(const matrix_t*);
extern bool stack_pop(void);
extern const matrix_t *stack_peek(void);

#endif /* _VMATH_MSTACK_H */
