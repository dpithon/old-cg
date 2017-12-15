#ifndef SHAPE_I
#define SHAPE_I

#define SHAPE_SURF_PLANE	0x0001
#define SHAPE_SURF_SPHERE	0x0002
#define SHAPE_SURF_CONE		0x0003
#define SHAPE_SURF_CYLINDER	0x0004
#define SHAPE_SURF_PARABOLOID	0x0005
#define SHAPE_MAX_ID		SHAPE_SURF_PARABOLOID


#define alloc_shape(xyz) ((struct xyz*) alloc_in_shape_pool(sizeof(struct xyz)))
extern void *alloc_in_shape_pool(size_t);
extern void  register_intersect_function(int, intersect_f);
extern void  register_normal_function(int, normal_f);

#endif /* SHAPE_I */
/*
vim: set syntax=c
*/

