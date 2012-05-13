#include <assert.h>
#include <stdio.h>
#include "math3d.h"

void pretty_printv(const char *s, struct hcoord  *u)
{
	printf("%s%6.2f %6.2f %6.2f %6.2f\n", s, u->x, u->y, u->z, u->w);
}

void pretty_printm(union matrix *m)
{
	pretty_printv("", &(m->rows.r1));
	pretty_printv("", &(m->rows.r2));
	pretty_printv("", &(m->rows.r3));
	pretty_printv("", &(m->rows.r4));
	printf("\n");
}


/* macros returning pointers to matrix vectors */
#define MTX_I(m)	&((m)->rows.r1)
#define MTX_J(m)	&((m)->rows.r2)
#define MTX_K(m)	&((m)->rows.r3)

int main()
{
	struct hcoord up = {0.5F, 1.F, 0.8F, 0.F };
	union matrix t_rot, rot = { .rows = { 
		.r1 = {6.F, 2.5F, 3.F, 0.F },
		.r4 = {0.F, 0.F, 0.F, 1.F } 
	} };
	union matrix trans;
	union matrix to_world, to_local;

	assert(! vector_is_null(MTX_I(&rot)));
	vector_unitize(&up);

	/* compute I */
	vector_unitize(MTX_I(&rot));

	/* compute J := Up - (I.Up).I */
	rot.rows.r2 = rot.rows.r1; /* J := I */
	vector_scale( MTX_J(&rot), -1.F * vector_dot(MTX_I(&rot), &up) );
	vector_unitize(vector_add(MTX_J(&rot), &up));

	/* compute K := I x J */
	vector_cross(MTX_K(&rot), MTX_I(&rot), MTX_J(&rot));
	
	/* Checking */
	assert(vector_is_unit(MTX_I(&rot)));
	assert(vector_is_unit(MTX_J(&rot)));
	assert(vector_is_unit(MTX_K(&rot)));
	assert(vectors_are_ortho(MTX_I(&rot), MTX_J(&rot)));
	assert(vectors_are_ortho(MTX_I(&rot), MTX_K(&rot)));
	assert(vectors_are_ortho(MTX_J(&rot), MTX_K(&rot)));

	/* M1 := Translate(v) . Rot */
	matrix_translation(&trans, 5.F, 6.F, -3.F);
	matrix_mul(&to_world, &trans, &rot);

	/* M2 := Inverse(M1)
	 *    := Inverse(Translate(v) . Rot)
	 *    := Inverse(Rot) . Inverse(Translate(v))
	 *    := Tranpose(Rot) . Translate(-v)
	 */
	matrix_translation(&trans, -5.F, -6.F, 3.F);
	matrix_transpose(&t_rot, &rot);
	matrix_mul(&to_local, &t_rot, &trans);

	pretty_printm(&to_local);
	pretty_printm(&to_world);
	pretty_printm(matrix_mul(&trans, &to_local, &to_world));


	/* samples ... */
	struct hcoord p1_in_world, p1_in_local = { 1.3F, 2.5F, -0.87F, 1.F };
	matrix_apply(&p1_in_world, &to_world, &p1_in_local);

	pretty_printv("p1 in world: ", &p1_in_world);
	pretty_printv("p1 in local: ", &p1_in_local);

	matrix_apply(&p1_in_local, &to_local, &p1_in_world);
	pretty_printv("p1 in world: ", &p1_in_world);
	pretty_printv("p1 in local: ", &p1_in_local);
	return 0;
}
