#include <stdio.h>
#include "math3d.h"

void pretty_print(const char *s, struct hcoord  *u)
{
	printf("%s %3.2f %3.2f %3.2f %3.2f\n", s, u->x, u->y, u->z, u->w);
}


int main()
{
	struct hcoord i = VECTOR_I;
	struct hcoord j = VECTOR_J;
	struct hcoord k = VECTOR_K;
	struct hcoord ij, jk, ki;
	struct hcoord ji, kj, ik;

	union matrix m = { .rows = { VECTOR_I, VECTOR_J, VECTOR_K, POINT_O } };

	pretty_print("i: ", &i);
	pretty_print("j: ", &j);
	pretty_print("k: ", &k);

	vector_cross(&ij, &i, &j);
	vector_cross(&ji, &j, &i);
	vector_cross(&jk, &j, &k);
	vector_cross(&kj, &k, &j);
	vector_cross(&ik, &i, &k);
	vector_cross(&ki, &k, &i);

	return 0;
}
