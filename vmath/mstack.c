#include <string.h>
#include "core.h"
#include "core_private.h" 
#include "mstack.h"


mstack_st mstack = {
	.i = 0,
	.m = { MAT_ID }
};


void stack_init_r(mstack_st *s)
{
	STO(17);

	s->i = 0;
	memcpy(&(s->m[0]), &matrix_id, sizeof matrix_id);
}


bool stack_push_r(mstack_st *s, const matrix_st *m) 
{
	ADD(3); CMP(1);

	if (s->i + 1 == MAX_STACK_SIZE) {
		return 1;
	}

	mulm(&(s->m[s->i + 1]), &(s->m[s->i]), (matrix_st*) m);
	++ s->i;

	return 0;
}


bool stack_pop_r(mstack_st *s)
{
	CMP(1); 
	ADD(s->i ? 1 : 0);

	if (s->i) {
		-- s->i;
		return 0;
	}

	return 1;
}


const matrix_st *stack_peek_r(mstack_st *s)
{
	return (const matrix_st*) &(s->m[s->i]);
}



bool stack_push(const matrix_st *s)
{
	return stack_push_r(&mstack, s);
}


bool stack_pop(void)
{
	return stack_pop_r(&mstack);
}


const matrix_st *stack_peek(void)
{
	return stack_peek_r(&mstack);
}
