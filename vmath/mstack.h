#ifndef _VMATH_MSTACK_H
#define _VMATH_MSTACK_H

/* Matrix stack */
#define MAX_STACK_SIZE	16
typedef struct mstack {
	matrix_st m[MAX_STACK_SIZE];
	int i;
} mstack_st;

extern void stack_init_r(mstack_st*);
extern bool stack_push_r(mstack_st*, const matrix_st*);
extern bool stack_pop_r(mstack_st*);
extern const matrix_st *stack_peek_r(mstack_st*);

extern bool stack_push(const matrix_st*);
extern bool stack_pop(void);
extern const matrix_st *stack_peek(void);

#endif /* _VMATH_MSTACK_H */
