/**
 * pinhole camera
 *
 */

#include <stdio.h>
#include <string.h>
#include <rt/vmath.h>

static coord_t os, is, js, ks;
static matrix_t m, mp;

/**
 * pinhole_coord_sys - compute pinhole basis and associated matrices
 *
 * s: pinhole coordinate
 * t: target point coordinates
 *
 * return false if s and t are the same point
 */
bool pinhole_coord_sys(coord_t *s, coord_t *t)
{
	matrix_t rot, tsl;
	coord_t minus_os;
	float p;

	if (is_pequal(s, t))
		return false;

	memcpy(&os, s, sizeof(coord_t));

	vector(&ks, s, t);
	unit_me(&ks);
	if (is_collinear(&ks, &vector_j, &p)) {
		if (p > 0.F) {
			memcpy(&is, &vector_k, sizeof(coord_t));
			memcpy(&js, &vector_i, sizeof(coord_t));
		} else {
			memcpy(&is, &vector_i, sizeof(coord_t));
			memcpy(&js, &vector_k, sizeof(coord_t));
		}
	} else {
		cross(&is, &ks, &vector_j);
		unit_me(&is);
		cross(&js, &ks, &is);
	}

	matrix(&m, &is, &js, &ks, &os);
	translation(&tsl, scale(&minus_os, &os, -1.F));
	matrixr(&rot, &is, &js, &ks, &point_o);
	matmat(&mp, &rot, &tsl);

	return true;
}

/*********************************************************************/

int main()
{
	vmiob_t iob;
	char buffer[200];
	coord_t s, t;
	matrix_t id;

	for (;;) {
		random_point(&s);
		random_point(&t);

		if (!pinhole_coord_sys(&s, &t)) {
			fprintf(stderr, "cannot compute pccs\n");
			init_iob(&iob, buffer, sizeof(buffer));
			printf("S: %s\n", dump_coord(&iob, &s));
			reset_iob(&iob);
			printf("T: %s\n", dump_coord(&iob, &t));
			return 1;
		}

		if (!is_pccs(&is, &js, &ks)) {
			/* should never happen */
			fprintf(stderr, "Not positive cartesian coordinate system\n");
			return 1;
		}

		matmat(&id, &m, &mp);
		if (!is_mequal(&id, &matrix_id)) {
			fprintf(stderr, "m.mp != id\n");
			init_iob(&iob, buffer, sizeof(buffer));
			fprintf(stderr, "S: %s\n", dump_coord(&iob, &s));
			reset_iob(&iob);
			fprintf(stderr, "T: %s\n", dump_coord(&iob, &t));
			return 1;
		}
	}

	return 0;
}
