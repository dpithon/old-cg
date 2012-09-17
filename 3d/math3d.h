#ifndef _MATH3D_H
#define _MATH3D_H

/* Homogeneous coordinates (w == 0: vector, w != 0: point) */
typedef struct coord {
	float x, y, z, w;
} coord_st;

/* Matrix 4x4 */
typedef struct matrix {
	float cell[4][4];
} matrix_st ;

/* Initalizer values */
#define VEC_I    { 1.F, 0.F, 0.F, 0.F }
#define VEC_J    { 0.F, 1.F, 0.F, 0.F }
#define VEC_K    { 0.F, 0.F, 1.F, 0.F }
#define PNT_O    { 0.F, 0.F, 0.F, 1.F }
#define PNT_I    { 1.F, 0.F, 0.F, 1.F }
#define PNT_J    { 0.F, 1.F, 0.F, 1.F }
#define PNT_K    { 0.F, 0.F, 1.F, 1.F }
#define MAT_ID { { 1.F, 0.F, 0.F, 0.F },\
		 { 0.F, 1.F, 0.F, 0.F },\
		 { 0.F, 0.F, 1.F, 0.F },\
		 { 0.F, 0.F, 0.F, 1.F } }

extern int        v_is_zero(const coord_st*);
extern int        v_is_unit(const coord_st*);
extern int        v_is_ortho(const coord_st*, const coord_st*);
extern float      v_len(const coord_st*);
extern float      v_dot(const coord_st*, const coord_st*); 
extern coord_st  *v_create(coord_st*, const coord_st*, const coord_st*);
extern coord_st  *v_scale(coord_st*, coord_st*, float);
extern coord_st  *v_unit(coord_st*, coord_st*);
extern coord_st  *v_add(coord_st*, coord_st*, coord_st*);
extern coord_st  *v_sub(coord_st*, coord_st*, coord_st*);
extern coord_st  *v_cross(coord_st*, const coord_st*, const coord_st*);
extern coord_st  *p_homogeneize(coord_st*, coord_st*);
extern coord_st  *m_mulc(coord_st*, const matrix_st*, coord_st*);
extern matrix_st *m_mulm(matrix_st*, matrix_st*, matrix_st*);
extern matrix_st *m_transpose(matrix_st*, matrix_st*);

#endif /* _MATH3D_H */
