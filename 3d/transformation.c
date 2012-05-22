#include "math3d.h"


union matrix *translation(union matrix *m, float x, float y, float z)
{
	m->cell[0][0] = 1.F;
	m->cell[0][1] = 0.F;
	m->cell[0][2] = 0.F;
	m->cell[0][3] = x;

	m->cell[1][0] = 0.F;
	m->cell[1][1] = 1.F;
	m->cell[1][2] = 0.F;
	m->cell[1][3] = y;

	m->cell[2][0] = 0.F;
	m->cell[2][1] = 0.F;
	m->cell[2][2] = 1.F;
	m->cell[2][3] = z;

	m->cell[3][0] = 0.F;
	m->cell[3][1] = 0.F;
	m->cell[3][2] = 0.F;
	m->cell[3][3] = 1.F;

	return m;
}

