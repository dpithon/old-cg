/**
 * pinhole camera
 *
 */

#include <stdio.h>
#include <string.h>
#include <vmath/vmath.h>

struct camera {
	coord_t o;
	coord_t i;
	coord_t j;
	coord_t k;

	float a;

	matrix_t m;
	matrix_t mp;
} camera;


static bool init(coord_t *s, coord_t *t)
{
	coord_t u, v = VEC_J;
	float p;

	vector(&camera.k, s, t);
	unit(&camera.k, &camera.k);

	if (is_collinear(&camera.k, &v, &p)) {
		if (p > 0.F) {
			memcpy(&camera.j, &vector_i, sizeof(coord_t));
			memcpy(&camera.i, &vector_k, sizeof(coord_t));
		} else {
			memcpy(&camera.j, &vector_k, sizeof(coord_t));
			memcpy(&camera.i, &vector_i, sizeof(coord_t));
		}
	} else {
		scale(&u, &camera.k, camera.k.y);
		sub(&camera.j, &v, &u);
		unit(&camera.j, &camera.j);

		cross(&camera.i, &camera.j, &camera.k);
	}

	if (!is_pccs(&camera.i, &camera.j, &camera.k)) {
		fprintf(stderr, "Not positive cartesian coordinate system\n");
		return false;
	}

	matrix(&camera.m, &camera.i, &camera.j, &camera.k, s);

	return true;
}


int main()
{
	vmiob_t iob;
	char buffer[200];

	coord_t s = {0, 4, 0, 1};
	coord_t t = {0, -6, 0, 1};

	init(&s, &t);

	init_iob(&iob, buffer, sizeof(buffer));
	printf("%s\n", dump_matrix(&iob, &camera.m));

	reset_iob(&iob);
	printf("%s", dump_matrix(&iob, &camera.mp));

	return 0;
}
