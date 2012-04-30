#include <stdio.h>
#include "vector.h"

void pretty_print(const char *s, struct vector *u)
{
	printf("%s %3.2f %3.2f %3.2f %3.2f\n", s, u->x, u->y, u->z, u->w);
}


int main()
{
	struct vector i = VECTOR_I;
	struct vector j = VECTOR_J;
	struct vector k = VECTOR_K;
	struct vector ij, jk, ki;
	struct vector ji, kj, ;

	pretty_print("i: ", &i);
	pretty_print("j: ", &j);
	pretty_print("k: ", &k);

	vector_cross(&ij, &i, &j);
	vector_cross(&ji, &j, &i);
	vector_cross(&jk, &j, &k);
	vector_cross(&kj, &k, &j);
	vector_cross(&jk, &j, &k);
	vector_cross(&kj, &k, &j);

	


	return 0;
}
