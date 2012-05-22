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


/* View transformation */
struct vt {
	struct hcoord vrp;	/* view reference point */
	struct hcoord lap;	/* "look at" point      */
	struct hcoord up;

	/* View transformation matrices */
	union matrix to_global; /* local coordinates to global ones */
	union matrix to_local;  /* global coordinates to local ones */
};

/* macros returning pointers to matrix vectors */
#define MTX_I(m)	&((m)->rows.r1)
#define MTX_J(m)	&((m)->rows.r2)
#define MTX_K(m)	&((m)->rows.r3)

/*
 * Compute view transformation matrices.
 * vt.vrp, vt.lap must be initialized.
 * vt.up must be a unit vector
 */
void compute_vt(struct vt *vt)
{
	union matrix m1, m2, tsl;

	/* Compute view coordinate system in matrix m1 */
	/* I := unit_vector(vrp, lap) */
	vec_from_point(MTX_I(&m1), &vt->vrp, &vt->lap);
	vec_unit_self(MTX_I(&m1));

	/* J := unit_vector(Up - (I.Up).I) */
	m1.rows.r2 = m1.rows.r1;
	vec_scale_self(MTX_J(&m1), -1.F * vec_dot(MTX_I(&m1), &vt->up) );
	vec_unit_self(vec_add_self(MTX_J(&m1), &vt->up));

	/* K := I x J */
	vec_cross(MTX_K(&m1), MTX_I(&m1), MTX_J(&m1));

	/* complete matrix */
	m1.cell[3][0] = m1.cell[3][1] = m1.cell[3][2] = 0.F;
	m1.cell[3][3] = 1.F;

	/* T1 := Translate(v) . Rot */
	translation(&tsl, vt->vrp.x, vt->vrp.y, vt->vrp.z);
	mat_mulm(&vt->to_global, &tsl, &m1);

	/* T2 := Inverse(T1)
	 *    := Inverse(Translate(v) . Rot)
	 *    := Inverse(Rot) . Inverse(Translate(v))
	 *    := Tranpose(Rot) . Translate(-v)
	 */
	mat_transpose(&m2, &m1);
	translation(&tsl, -vt->vrp.x, -vt->vrp.y, -vt->vrp.z);
	mat_mulm(&vt->to_local, &m2, &tsl);
}


int main()
{
	union matrix tmp;
	struct vt vt = { 
		.vrp = { 4.F, 3.F, 2.F, 1.F },
		.lap = { 8.F, 5.F, 4.F, 1.F },
		.up  = VEC_J
	};

	compute_vt(&vt);

	pretty_printm(&vt.to_global);
	pretty_printm(&vt.to_local);
	pretty_printm(mat_mulm(&tmp, &vt.to_local, &vt.to_global));


	/* samples ... */
	struct hcoord pntg, pnt = { 1.F, 1.F, 1.F, 1.F };

	pretty_printv("p in local cs  : ", &pnt);
	mat_mulv(&pntg, &vt.to_global, &pnt);
	pretty_printv("p in global cs : ", &pntg);
	mat_mulv(&pnt, &vt.to_local, &pntg);
	pretty_printv("p in local cs  : ", &pnt);

	return 0;
}
