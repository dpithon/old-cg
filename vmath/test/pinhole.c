/**
 * pinhole camera
 *
 */

#include <stdio.h>
#include <string.h>
#include <rt/vmath.h>

matrix_t m;
matrix_t mp;


static bool init(coord_t *s, coord_t *t)
{
	coord_t i, j, k, u, v = VEC_J;
	matrix_t rot, tsl;
	float p;

	vector(&k, s, t);
	unit_me(&k);

	if (is_collinear(&k, &v, &p)) {
		if (p > 0.F) {
			memcpy(&j, &vector_i, sizeof(coord_t));
			memcpy(&i, &vector_k, sizeof(coord_t));
		} else {
			memcpy(&j, &vector_k, sizeof(coord_t));
			memcpy(&i, &vector_i, sizeof(coord_t));
		}
	} else {
		scale(&u, &k, k.y);
		sub(&j, &v, &u);
		unit_me(&j);

		cross(&i, &j, &k);
	}

	if (!is_pccs(&i, &j, &k)) {
		fprintf(stderr, "Not positive cartesian coordinate system\n");
		return false;
	}

	matrix(&m, &i, &j, &k, s);

	u.x = -s->x;
	u.y = -s->y;
	u.z = -s->z;
	u.w = 0.F;
	translation(&tsl, &u);
	matrixr(&rot, &i, &j, &k, &point_o);
	matmat(&mp, &rot, &tsl);

	return true;
}


int main()
{
	vmiob_t iob;
	char buffer[200];
	matrix_t id;

	coord_t s = {13.2, 14, -32, 1};
	coord_t t = {0, 0, 0, 1};

	init(&s, &t);

	init_iob(&iob, buffer, sizeof(buffer));
	printf("%s\n", dump_matrix(&iob, &m));

	reset_iob(&iob);
	printf("%s\n", dump_matrix(&iob, &mp));

	matmat(&id, &m, &mp);
	reset_iob(&iob);
	printf("%s", dump_matrix(&iob, &id));

	return 0;
}
