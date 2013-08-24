/**
 ** Test de rotation autour d'un axe quelconque
 ** $ rotation x y z theta_deg px py pz
 */

#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "core.h"
#include "mstack.h"
#include "io.h"

#define PI 3.141592654f

int build_rotation(matrix_st *rot, const coord_st *u, float theta)
{
	float v;
	matrix_st m1, tm1, m2, tm2, m3;
	int idx = 0;
	#define SZ 2000
	char buf[SZ];
	mstack_st stck;

	assert( is_unit(u) );

	/* R1 (rotation autour de z pour amener u dans xOz) */
	v = sqrtf(u->x * u->x  +  u->y * u->y);
	memcpy(&m1, &matrix_id, sizeof m1);
	m1.cell[0][0] =  u->x / v;
	m1.cell[0][1] =  u->y / v;
	m1.cell[1][0] = -u->y / v;
	m1.cell[1][1] =  u->x / v;
	transpose(&tm1, &m1);

	/* R2 (rotation autour de y afin d'amener u sur z */
	memcpy(&m2, &matrix_id, sizeof m2);
	m2.cell[0][0] =  u->z;
	m2.cell[0][2] = -v;
	m2.cell[2][0] =  v;
	m2.cell[2][2] =  u->z;
	transpose(&tm2, &m2);

	/* R3 (rotation autour de z d'un angle theta) */
	rotationz(&m3, theta);

	/* stack_save() */
	
	stack_push(&tm1);
	stack_push(&tm2);
	stack_push(&m3);
	stack_push(&m2);
	stack_push(&m1);
	memcpy(rot, stack_peek(), sizeof(matrix_st));
	/* stack_restore() */

	dump_stack(buf, SZ, &idx, 0);
	idx = 0;
	if (load_stack(buf, SZ, &idx, &stck)) {
		printf("error\n");
		return 1;
	}
	prints(0, &stck);
	

	return 0;
}


int main(int argc, char *argv[])
{
	float theta;
	coord_st u;
	matrix_st rot1, rot2;
	coord_st p, rt1, rt2;

	if (argc < 8) {
		fprintf(stderr, "%s x y z theta_deg px py pz\n", argv[0]);
		return 1;
	}

	u.x   = atof(argv[1]);
	u.y   = atof(argv[2]);
	u.z   = atof(argv[3]);
	u.w   = 0.f;
	theta = atof(argv[4]) * PI / 180.f;
	unit(&u, &u);
	p.x   = atof(argv[5]);
	p.y   = atof(argv[6]);
	p.z   = atof(argv[7]);
	p.w   = 1.f;
	
	if (build_rotation(&rot1, &u, theta)) {
		return 2;
	}

	rotation(&rot2, &u, theta);

	mulc(&rt1, &rot1, &p);
	mulc(&rt2, &rot2, &p);

	return 0;
}
