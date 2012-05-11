#include <stdio.h>
#include "math3d.h"

void pretty_printv(const char *s, struct hcoord  *u)
{
	printf("%s %6.2f %6.2f %6.2f %6.2f\n", s, u->x, u->y, u->z, u->w);
}

void pretty_printm(union matrix *m)
{
	pretty_printv("", &(m->rows.r1));
	pretty_printv("", &(m->rows.r2));
	pretty_printv("", &(m->rows.r3));
	pretty_printv("", &(m->rows.r4));
	printf("\n");
}


#define VecI(m)	(&(m).rows.r1)
#define VecJ(m)	(&(m).rows.r2)
#define VecK(m)	(&(m).rows.r3)

int main()
{
	struct hcoord up = {0.F, 1.F, 2.F, 0.F };
	union matrix id, tm, m = { .rows = { 
		.r1 = {6.F, 2.5F, 3.F, 0.F },
		.r4 = {0.F, 0.F, 0.F, 1.F } 
	} };

	vector_unitize(VecI(m));
	m.rows.r2 = m.rows.r1;
	vector_scale(VecJ(m), -1.F * vector_dot(VecI(m), &up));
	vector_unitize(vector_add(VecJ(m), &up));
	vector_cross(VecK(m), VecI(m), VecJ(m));
	
	pretty_printm(&m);

	pretty_printm(matrix_transpose(&tm, &m));
	pretty_printm(matrix_mul(&id, &tm, &m));
	pretty_printm(matrix_mul(&id, &m, &tm));

	return 0;
}
