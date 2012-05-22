#include <assert.h>
#include <stdio.h>
#include "geom/math3d.h"
#include "geom/modelops.h"
#include "geom/transformation.h"
#include "bpix/bpix.h"

void printv(struct hcoord  *u)
{
	printf("%6.2f %6.2f %6.2f %6.2f", u->x, u->y, u->z, u->w);
}

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

	/* Compute global coordinate system in matrix m1 */
	/* n := unit_vector(vrp, lap) */
	vec_from_point(MTX_K(&m1), &vt->vrp, &vt->lap);
	vec_unit_self(MTX_K(&m1));

	/* v := unit_vector(Up - (n.Up).n) */
	m1.rows.r2 = m1.rows.r3;
	vec_scale_self(MTX_J(&m1), -1.F * vec_dot(MTX_K(&m1), &vt->up) );
	vec_unit_self(vec_add_self(MTX_J(&m1), &vt->up));

	/* u := J x K */
	vec_cross(MTX_I(&m1), MTX_J(&m1), MTX_K(&m1));

	/* complete matrix */
	m1.cell[3][0] = m1.cell[3][1] = m1.cell[3][2] = 0.F;
	m1.cell[3][3] = 1.F;

	assert(vec_is_unit(MTX_I(&m1)));
	assert(vec_is_unit(MTX_J(&m1)));
	assert(vec_is_unit(MTX_K(&m1)));
	assert(vec_is_ortho(MTX_I(&m1), MTX_J(&m1)));
	assert(vec_is_ortho(MTX_J(&m1), MTX_K(&m1)));
	assert(vec_is_ortho(MTX_K(&m1), MTX_I(&m1)));


	/* T1 := Translate(v) . Rot */
	translation(&tsl, -vt->vrp.x, -vt->vrp.y, -vt->vrp.z);
	mat_mulm(&vt->to_global, &m1, &tsl);
	pretty_printm(&vt->to_global);

	/* T2 := Inverse(T1)
	 *    := Inverse(Translate(v) . Rot)
	 *    := Inverse(Rot) . Inverse(Translate(v))
	 *    := Tranpose(Rot) . Translate(-v)
	 */
	mat_transpose(&m2, &m1);
	translation(&tsl, vt->vrp.x, vt->vrp.y, vt->vrp.z);
	mat_mulm(&vt->to_local, &tsl, &m2);
}



struct hcoord point[] = {
	{  0, 10, 54, 1 },
	{  8, 16, 54, 1 },
	{ 16, 10, 54, 1 },
	{ 16,  0, 54, 1 },
	{  0,  0, 54, 1 },
	{  0, 10, 30, 1 },
	{  8, 16, 30, 1 },
	{ 16, 10, 30, 1 },
	{ 16,  0, 30, 1 },
	{  0,  0, 30, 1 },

	{  0,  0,  0, 1},
	{  10,  0,  0, 1},
	{  0,  200,  0, 1},
	{  0,  0,  100, 1},

	{  0,  0,  0, 0 }
};

struct edge {
	int start, end;
} edge[] = {
	{0, 1}, {1, 2}, {2, 3}, {3, 4}, {4, 0},
	{5, 6}, {6, 7}, {7, 8}, {8, 9}, {9, 5},
	{0, 5}, {1, 6}, {2, 7}, {3, 8}, {4, 9},
	{10, 11}, {10, 12}, {10, 13},

	{-1, -1}
};

/*
struct hcoord point[] = {
	{ -100,  100, -100, 1 },
	{  100,  100, -100, 1 },
	{  100, -100, -100, 1 },
	{ -100, -100, -100, 1 },
	{ -100,  100,  100, 1 },
	{  100,  100,  100, 1 },
	{  100, -100,  100, 1 },
	{ -100, -100,  100, 1 },
	{    0,  150, -100, 1 },
	{    0,  150,  100, 1 },
	{    0,    0,    0, 0 }
};

struct edge {
	int start, end;
} edge[] = {
	{0, 1}, {1, 2}, {2, 3}, {3, 0},
	{4, 5}, {5, 6}, {6, 7}, {7, 4},
	{0, 4}, {1, 5}, {2, 6}, {3, 7},
	{0, 8}, {8, 1}, {4, 9}, {9, 5},
	{8, 9},
	{-1, -1}
};
*/

#define D 50.F

int main()
{
	int i = 0;
	struct vt vt = {
		.vrp = {   60,  60, 60, 1 },
		.lap = {   0,   0,   0, 1 },
		.up  = {   0,   -1,   0, 0 }
	};
	union matrix m, persp = { .rows = {
		{1, 0, 0, 0},
		{0, 1, 0, 0},
		{0, 0, 1, 0},
		{0, 0, 1.F / D, 1.F}
	} };

	struct hcoord p2d;
	struct bpix bp;
	struct gctx gc;

	compute_vt(&vt);

	mat_mulm(&m, &persp, &vt.to_global);

	model_load_id();
	model_push();
	model_scale(2, 2, 2);
	/*
	model_translate(0, 0, 0);
	model_rotate_x(-90);
	model_rotate_y(-90);
		*/

	for (i = 0; point[i].w != 0; i++) {
		if (i == 10) {
			model_pop();
		}
		model_vertex(&point[i]);
		mat_mulv(&p2d, &m, &point[i]);
		point[i] = p2d;
		homogeneize(&point[i]);
		vec_scale_self(&point[i], 4);
	}

	if ( bpix_init(&bp, 800, 800) ) {
		fprintf(stderr, "bpix error: %s\n", bpix_get_errstr(&bp));
		return 1;
	}

	gc.fg_r = 255;
	gc.fg_g = 255;
	gc.fg_b = 255;

	for (i = 0; edge[i].start >= 0; i++) {
		bpix_draw_linei(&bp, &gc, 
			400+point[edge[i].start].x, 400+point[edge[i].start].y,
			400+point[edge[i].end].x, 400+point[edge[i].end].y);
	}

	bpix_draw_linei(&bp, &gc, 400 - 84, 400 - 84, 400 + 84, 400 - 84);
	bpix_draw_linei(&bp, &gc, 400 + 84, 400 - 84, 400 + 84, 400 + 84);
	bpix_draw_linei(&bp, &gc, 400 + 84, 400 + 84, 400 - 84, 400 + 84);
	bpix_draw_linei(&bp, &gc, 400 - 84, 400 + 84, 400 - 84, 400 - 84);

	if ( bpix_pnm_write_to_file(&bp, "cube.pnm") || 
	     bpix_cleanup(&bp) ) {
		fprintf(stderr, "bpix error: %s\n", bpix_get_errstr(&bp));
		return 1;
	}
	return 0;
}
