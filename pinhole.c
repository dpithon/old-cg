/**
 * pinhole camera
 *
 */

matrix_t m, mp;

bool pinhole(coord_t *s, coord_t *t, float a)
{
	coord_t i, j, k;

	unit(k, vector(k, s, t));
	unit(j, sub(j, vector_j, scale(j, k, dot(vector_j, k))));
	cross(i, j, k);
}

