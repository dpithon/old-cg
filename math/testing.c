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
#include "iob.h"
#include "settings.h"

#define PI 3.141592654f

static void check_dump_and_load_coord(const coord_t*);
static void check_dump_and_load_matrix(const matrix_t*);
static void check_dump_and_load_mstack(const mstack_t*);

int build_rotation(matrix_t *rot, const coord_t *u, float theta)
{
	float v;
	matrix_t m1, tm1, m2, tm2, m3;

	assert( is_vunit(u) );

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
	memcpy(rot, stack_peek(), sizeof(matrix_t));
	/* stack_restore() */

	return 0;
}


#define BUFSZ 8192
vmiob_t iob;
char buf[BUFSZ];
int main(int argc, char *argv[])
{
	float theta;
	coord_t u;
	matrix_t rot1, rot2;
	coord_t p, rt1, rt2;

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

	matcol(&rt1, &rot1, &p);
	matcol(&rt2, &rot2, &p);

	check_dump_and_load_coord(&rt1);
	check_dump_and_load_matrix(&rot1);
	check_dump_and_load_mstack(0);

	return 0;
}


static void check_dump_and_load_coord(const coord_t *c)
{
	char buf[80];
	vmiob_t iob;
	coord_t d;

	// dump c to human readable string
	init_iob(&iob, buf, 80);
	printf("c (asc): [%s]\n", dump_coord(&iob, c));

	// dump c to hex string
	reset_iob(&iob);
	switch_iob(&iob);
	printf("c (hex): [%s]\n", dump_coord(&iob, c));

	// load d from hex string
	reset_iob(&iob);
	load_coord(&d, &iob);

	// dump d to human readable string
	reset_iob(&iob);
	switch_iob(&iob);
	printf("d (asc): [%s]\n", dump_coord(&iob, &d));

	// dump d to hex string
	reset_iob(&iob);
	switch_iob(&iob);
	printf("d (hex): [%s]\n", dump_coord(&iob, &d));
}


static void check_dump_and_load_matrix(const matrix_t *m)
{
	char buf[180];
	vmiob_t iob;
	matrix_t n;

	// dump m to human readable string
	init_iob(&iob, buf, 180);
	printf("m (asc):\n%s\n", dump_matrix(&iob, m));

	// dump m to hex string
	reset_iob(&iob);
	switch_iob(&iob);
	printf("m (hex):\n%s\n", dump_matrix(&iob, m));

	// load n from hex string
	reset_iob(&iob);
	load_matrix(&n, &iob);

	// dump n to human readable string
	reset_iob(&iob);
	switch_iob(&iob);
	printf("n (asc):\n%s\n", dump_matrix(&iob, &n));

	// dump n to hex string
	reset_iob(&iob);
	switch_iob(&iob);
	printf("n (hex):\n%s\n", dump_matrix(&iob, &n));
}


static void check_dump_and_load_mstack(const mstack_t *s)
{
	char buf[4000];
	vmiob_t iob;
	mstack_t t;

	// dump s to human readable string
	init_iob(&iob, buf, 4000);
	printf("s (asc):\n%s\n", dump_mstack(&iob, s));

	// dump s to hex string
	reset_iob(&iob);
	switch_iob(&iob);
	printf("s (hex):\n%s\n", dump_mstack(&iob, s));

	// load t from hex string
	reset_iob(&iob);
	load_mstack(&t, &iob);

	// dump t to human readable string
	reset_iob(&iob);
	switch_iob(&iob);
	printf("t (asc):\n%s\n", dump_mstack(&iob, &t));

	// dump t to hex string
	reset_iob(&iob);
	switch_iob(&iob);
	printf("t (hex):\n%s\n", dump_mstack(&iob, &t));
}
