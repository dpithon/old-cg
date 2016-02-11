/**
 * pinhole camera
 *
 */

#include <stdio.h>
#include <vmath/vmath.h>

bool pinhole(matrix_t *m, coord_t *s, coord_t *t)
{
	coord_t i, j, k, v = {0, 1, 0, 0};

	unit(&k, vector(&k, s, t));
	unit(&j, sub(&j, &v, scale(&j, &k, dot(&vector_j, &k))));
	cross(&i, &j, &k);

	if (!is_pccs(&i, &j, &k)) {
		fprintf(stderr, "base non orthonormée directe\n");
		return false;
	}

	matrix(m, &i, &j, &k, s);

	return true;
}

int main()
{
	matrix_t m, mp;
	vmiob_t iob;
	char buffer[200];

	coord_t s = {12, 4, 28, 1};
	coord_t t = {34, -6, 12, 1};

	pinhole(&m, &s, &t);

	init_iob(&iob, buffer, sizeof(buffer));

	printf("%s\n", dump_matrix(&iob, &m));

	reset_iob(&iob);

	printf("%s", dump_matrix(&iob, &mp));

	return 0;
}
