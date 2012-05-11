#include <stdio.h>
#include "math3d.h"

void pretty_printv(const char *s, struct hcoord  *u)
{
	printf("%s %3.2f %3.2f %3.2f %3.2f\n", s, u->x, u->y, u->z, u->w);
}

void pretty_printm(union matrix *m)
{
	pretty_printv("", &(m->rows.r1));
	pretty_printv("", &(m->rows.r2));
	pretty_printv("", &(m->rows.r3));
	pretty_printv("", &(m->rows.r4));
}


int main()
{
	struct hcoord i = VECTOR_I;
	struct hcoord j = VECTOR_J;
	struct hcoord k = VECTOR_K;
	struct hcoord ij, jk, ki;
	struct hcoord ji, kj, ik;

	union matrix m = { .rows = { VECTOR_I, VECTOR_J, VECTOR_K, POINT_O } };

	pretty_printv("i: ", &i);
	pretty_printv("j: ", &j);
	pretty_printv("k: ", &k);

	vector_cross(&ij, &i, &j);
	vector_cross(&ji, &j, &i);
	vector_cross(&jk, &j, &k);
	vector_cross(&kj, &k, &j);
	vector_cross(&ik, &i, &k);
	vector_cross(&ki, &k, &i);

	pretty_printm(&m);
	m.rows.r1 = k;
	pretty_printm(&m);
	return 0;
}
