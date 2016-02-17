#include <string.h>
#include "core.h"
#include "mstack.h"


mstack_t vmath_mstack = {
	.i = 0,
	.m = { MATRIX_ID }
};


void stack_init_r(mstack_t *s)
{
	s->i = 0;
	memcpy(&(s->m[0]), &MatrixId, sizeof MatrixId);
}


bool stack_push_r(mstack_t *s, const matrix_t *m) 
{
	if (s->i + 1 == MAX_STACK_SIZE) {
		return 1;
	}

	matmat(&(s->m[s->i + 1]), &(s->m[s->i]), (matrix_t*) m);
	++ s->i;

	return 0;
}


bool stack_pop_r(mstack_t *s)
{
	if (s->i) {
		-- s->i;
		return 0;
	}

	return 1;
}


const matrix_t *stack_peek_r(mstack_t *s)
{
	return (const matrix_t*) &(s->m[s->i]);
}



bool stack_push(const matrix_t *s)
{
	return stack_push_r(&vmath_mstack, s);
}


bool stack_pop(void)
{
	return stack_pop_r(&vmath_mstack);
}


const matrix_t *stack_peek(void)
{
	return stack_peek_r(&vmath_mstack);
}
