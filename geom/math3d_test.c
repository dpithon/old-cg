#include <assert.h>
#include <stdio.h>
#include "math3d.h"

void pretty_printv(const char *s, struct hcoord  *u)
{
	printf("%s%6.2f %6.2f %6.2f %6.2f\n", s, u->x, u->y, u->z, u->w);
}

void pretty_printm(union matrix *m)
{
	pretty_printv("", &(m->rows.r1));
	pretty_printv("", &(m->rows.r2));
	pretty_printv("", &(m->rows.r3));
	pretty_printv("", &(m->rows.r4));
	printf("\n");
}


#define MTX_I(m)	&((m)->rows.r1)
#define MTX_J(m)	&((m)->rows.r2)
#define MatrixK(m)	&((m)->rows.r3)

int main()
{
	struct hcoord up = {0.F, 1.F, 0.F, 0.F };
	union matrix tm, m = { .rows = { 
		.r1 = {6.F, 2.5F, 3.F, 0.F },
		.r4 = {0.F, 0.F, 0.F, 1.F } 
	} };

	assert_vector_not_null( MTX_I(&m) );
	assert_vector_is_unit( &up );

	vector_unitize( MTX_I(&m) );
	MTX_J(m) = MTX_I(m);
	vector_scale( &MTX_J(m), -1.F * vector_dot(&MTX_I(m), &up) );
	vector_unitize(vector_add(&MTX_J(m), &up));
	vector_cross(&MatrixK(m), &MTX_I(m), &MTX_J(m));
	
	matrix_transpose(&tm, &m);

	return 0;
}
