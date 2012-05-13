#include <assert.h>
#include <stdio.h>
#include "math3d.h"
#include "transformation.h"

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

	assert(! vec_is_null(MTX_I(&rot)));
	vec_unit_self(&up);

	/* compute I */
	vec_unit_self(MTX_I(&rot));

	/* compute J := Up - (I.Up).I */
	rot.rows.r2 = rot.rows.r1; /* J := I */
	vec_scale_self( MTX_J(&rot), -1.F * vec_dot(MTX_I(&rot), &up) );
	vec_unit_self(vec_add_self(MTX_J(&rot), &up));

	/* compute K := I x J */
	vec_cross(MTX_K(&rot), MTX_I(&rot), MTX_J(&rot));
	
	/* Checking */
	assert(vec_is_unit(MTX_I(&rot)));
	assert(vec_is_unit(MTX_J(&rot)));
	assert(vec_is_unit(MTX_K(&rot)));
	assert(vec_is_ortho(MTX_I(&rot), MTX_J(&rot)));
	assert(vec_is_ortho(MTX_I(&rot), MTX_K(&rot)));
	assert(vec_is_ortho(MTX_J(&rot), MTX_K(&rot)));

	/* M1 := Translate(v) . Rot */
	translation(&trans, 5.F, 6.F, -3.F);
	mat_x_mat(&to_world, &trans, &rot);

	/* M2 := Inverse(M1)
	 *    := Inverse(Translate(v) . Rot)
	 *    := Inverse(Rot) . Inverse(Translate(v))
	 *    := Tranpose(Rot) . Translate(-v)
	 */
	translation(&trans, -5.F, -6.F, 3.F);
	mat_transpose(&t_rot, &rot);
	mat_x_mat(&to_local, &t_rot, &trans);

	pretty_printm(&to_local);
	pretty_printm(&to_world);
	pretty_printm(mat_x_mat(&trans, &to_local, &to_world));


	/* samples ... */
	struct hcoord p1_in_world, p1_in_local = { 1.3F, 2.5F, -0.87F, 1.F };
	mat_x_vec(&p1_in_world, &to_world, &p1_in_local);

	pretty_printv("p1 in world: ", &p1_in_world);
	pretty_printv("p1 in local: ", &p1_in_local);

	mat_x_vec(&p1_in_local, &to_local, &p1_in_world);
	pretty_printv("p1 in world: ", &p1_in_world);
	pretty_printv("p1 in local: ", &p1_in_local);
	return 0;
}
