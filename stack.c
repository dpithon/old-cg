#include "vmath.h"
#include "stack.h"
#include "debug.h"

#define STACK_SIZE 16
#define MAX_INDEX  (STACK_SIZE - 1)

static int index;
static struct matrix stack[STACK_SIZE] = { MATRIX_ID };
static struct matrix mat;


void translate(double x, double y, double z)
{
	static struct coord t = POINT_O;

	if (index < MAX_INDEX) {
		t.x = x;
		t.y = y;
		t.z = z;
		translation(&mat, &t);
		matmat(&stack[index + 1], &stack[index], &mat);
		index ++;
	} else {
		fatal("stack overflow");
	}
}


void rotate_x(double deg)
{
	if (index < MAX_INDEX) {
		rotationx(&mat, deg * M_PI / 180.);
		matmat(&stack[index + 1], &stack[index], &mat);
		index ++;
	} else {
		fatal("stack overflow");
	}
}


void rotate_y(double deg)
{
	if (index < MAX_INDEX) {
		rotationy(&mat, deg * M_PI / 180.);
		matmat(&stack[index + 1], &stack[index], &mat);
		index ++;
	} else {
		fatal("stack overflow");
	}
}


void rotate_z(double deg)
{
	if (index < MAX_INDEX) {
		rotationz(&mat, deg * M_PI / 180.);
		matmat(&stack[index + 1], &stack[index], &mat);
		index ++;
	} else {
		fatal("stack overflow");
	}
}




void pop(void)
{
	if (index)
		--index;
	else
		fatal("stack underflow");
}


void reset(void)
{
	index = 0;
}


void transform(struct coord *c)
{
	matcol_in_place(c, &stack[index]);
}
