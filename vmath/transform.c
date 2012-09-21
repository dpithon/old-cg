#include <assert.h>
#include <string.h>
#include "vmath.h"
#include "transform.h"

static struct transform_st {
	matrix_st t, rt;
} trn = {
	.t  = MAT_ID,
	.rt = MAT_ID
};

#define T(i,j)	(trn.t.cell[i][j])
#define RT(i,j)	(trn.rt.cell[i][j])

/* set current transformation to Id */
void t_id(void)
{
	memcpy(&trn.t, &matrix_id, sizeof trn.t);
	memcpy(&trn.rt, &matrix_id, sizeof trn.rt);
}


/* apply rotation about (x,y,z) axis to current transformarion */
void t_rotate(float x, float y, float z, float deg)
{
}


/* apply translation to current transformation */
void t_translate(float x, float y, float z)
{
	float mx = -x, my = -y, mz = -z;

	T(0,3) = T(0,1)*x + T(0,2)*y + T(0,3)*z + T(0,4);
	T(1,3) = T(1,1)*x + T(1,2)*y + T(1,3)*z + T(1,4);
	T(2,3) = T(2,1)*x + T(2,2)*y + T(2,3)*z + T(2,4);
	T(3,3) = T(3,1)*x + T(3,2)*y + T(3,3)*z + T(3,4);

	RT(0,3) = RT(0,1)*mx + RT(0,2)*my + RT(0,3)*mz + RT(0,4);
	RT(1,3) = RT(1,1)*mx + RT(1,2)*my + RT(1,3)*mz + RT(1,4);
	RT(2,3) = RT(2,1)*mx + RT(2,2)*my + RT(2,3)*mz + RT(2,4);
	RT(3,3) = RT(3,1)*mx + RT(3,2)*my + RT(3,3)*mz + RT(3,4);
}


/* apply shearing to current transformation */
void t_shear(float x, float y, float z)
{
}


/* apply scaling to current transformation */
void t_scale(float x, float y, float z)
{
	float ix, iy, iz;

	assert(x != 0.F);
	assert(y != 0.F);
	assert(z != 0.F);

	ix = 1.F / x;
	iy = 1.F / y;
	iz = 1.F / z;

	T(0,0) *= x; T(0, 1) *= y; T(0, 2) *= z;
	T(1,0) *= x; T(1, 1) *= y; T(1, 2) *= z;
	T(2,0) *= x; T(2, 1) *= y; T(2, 2) *= z;
	T(3,0) *= x; T(3, 1) *= y; T(3, 2) *= z;

	RT(0,0) *= ix; RT(0, 1) *= iy; RT(0, 2) *= iz;
	RT(1,0) *= ix; RT(1, 1) *= iy; RT(1, 2) *= iz;
	RT(2,0) *= ix; RT(2, 1) *= iy; RT(2, 2) *= iz;
	RT(3,0) *= ix; RT(3, 1) *= iy; RT(3, 2) *= iz;
}
