#ifndef _VMATH_H
#define _VMATH_H

#include <stdbool.h>

/* Homogeneous coordinates (w == 0: vector, w != 0: point) */
typedef struct coord {
	float x, y, z, w;
} coord_st;

/* Matrix (4x4) */
typedef struct matrix {
	float cell[4][4];
} matrix_st;

/* Matrix stack */
#define MAX_STACK_SIZE	16
typedef struct mstack {
	matrix_st m[MAX_STACK_SIZE];
	int i;
} mstack_st;


/* Initalizer values */
#define VEC_I    { 1.F, 0.F, 0.F, 0.F }
#define VEC_J    { 0.F, 1.F, 0.F, 0.F }
#define VEC_K    { 0.F, 0.F, 1.F, 0.F }
#define PNT_O    { 0.F, 0.F, 0.F, 1.F }
#define PNT_I    { 1.F, 0.F, 0.F, 1.F }
#define PNT_J    { 0.F, 1.F, 0.F, 1.F }
#define PNT_K    { 0.F, 0.F, 1.F, 1.F }
#define MAT_ID   { .cell = { { 1.F, 0.F, 0.F, 0.F },\
			     { 0.F, 1.F, 0.F, 0.F },\
			     { 0.F, 0.F, 1.F, 0.F },\
			     { 0.F, 0.F, 0.F, 1.F } } }

#define self_scale(v, a) scale((v), (v), (a))
#define self_unit(v)	 unit((v), (v))

extern bool       is_point(const coord_st*);
extern bool       is_vector(const coord_st*);
extern bool       is_zero(const coord_st*);
extern bool       is_unit(const coord_st*);
extern bool       is_ortho(const coord_st*, const coord_st*);

extern float      len(const coord_st*);
extern float      dot(const coord_st*, const coord_st*); 
extern coord_st  *vector(coord_st*, const coord_st*, const coord_st*);
extern coord_st  *scale(coord_st*, coord_st*, float);
extern coord_st  *unit(coord_st*, coord_st*);
extern coord_st  *add(coord_st*, coord_st*, coord_st*);
extern coord_st  *sub(coord_st*, coord_st*, coord_st*);
extern coord_st  *cross(coord_st*, const coord_st*, const coord_st*);
extern coord_st  *homogeneize(coord_st*, coord_st*);
extern coord_st  *mulc(coord_st*, const matrix_st*, coord_st*);
extern matrix_st *mulm(matrix_st*, matrix_st*, matrix_st*);
extern matrix_st *transpose(matrix_st*, matrix_st*);
extern matrix_st *rotationx(matrix_st*, float);
extern matrix_st *rotationy(matrix_st*, float);
extern matrix_st *rotationz(matrix_st*, float);
extern matrix_st *rotation(matrix_st*, const coord_st*, float);
extern matrix_st *scaling(matrix_st*, float, float, float);
extern matrix_st *translation(matrix_st*, coord_st*);

extern void stack_init_r(mstack_st*);
extern bool stack_push_r(mstack_st*, const matrix_st*);
extern bool stack_pop_r(mstack_st*);
extern const matrix_st *stack_peek_r(mstack_st*);

extern bool stack_push(const matrix_st*);
extern bool stack_pop(void);
extern const matrix_st *stack_peek(void);

extern const matrix_st matrix_id;
extern const coord_st  vector_i;
extern const coord_st  vector_j;
extern const coord_st  vector_k;
extern const coord_st  point_o;
extern mstack_st mstack;

#endif /* _VMATH_H */
