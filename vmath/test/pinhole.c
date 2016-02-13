/**
 * pinhole camera
 *
 */

#include <assert.h>
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
	assert(is_point(s));
	assert(is_point(t));

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

	assert(is_pccs(&is, &js, &ks));
	return true;
}

/*********************************************************************/

int main()
{
	coord_t s, t, v, vv, w;
	matrix_t id;

	random_point(&s);
	random_point(&t);
	random_vector(&v);

	if (!pinhole_coord_sys(&s, &t)) {
		printf("cannot compute pccs\n");
		print_coord("S", &s);
		print_coord("T", &s);
		return 1;
	}

	matmat(&id, &m, &mp);
	if (!is_mequal(&id, &matrix_id)) {
		printf("m.mp != id\n");
		print_coord("S", &s);
		print_coord("T", &s);
		return 1;
	}

	matcol(&w, &m, &v);
	matcol(&vv, &mp, &w);

	if (!is_vequal(&v, &vv)) {
		printf("mp.m.v != v\n");
		print_coord("S", &s);
		print_coord("T", &s);
		return 1;
	}

	print_coord("V ", &v);
	print_coord("W ", &w);
	print_coord("V'", &vv);
	return 0;
}
