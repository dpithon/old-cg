#ifndef SHAPE_H
#define SHAPE_H

#include <stddef.h>

#include "slink.h"
#include "types.h"
#include "vmath.h"

#define SHAPE_SURF_PLANE	0x0001
#define SHAPE_SURF_SPHERE	0x0002
#define SHAPE_SURF_CONE		0x0003
#define SHAPE_SURF_CYLINDER	0x0004
#define SHAPE_SURF_PARABOLOID	0x0005
#define SHAPE_MAX_ID		SHAPE_SURF_PARABOLOID

#define SHAPE(s)	((struct shape*)(s))

struct shape {
	struct slink slink; // slink MUST be the first field !

	int shape_type;

	struct cs cs;
	struct matrix cam_to_shp;
	struct matrix shp_to_cam;

	struct material *material[2];
};


#define alloc_shape(xyz) ((struct xyz*) alloc_in_shape_pool(sizeof(struct xyz)))
extern void *alloc_in_shape_pool(size_t);
extern void  register_intersect_function(int, intersect_f);
extern void  register_normal_function(int, normal_f);
extern bool  intersect(struct hit*, const struct ray*, const struct shape*);
extern void  normal(struct coord*, const struct hit*);

extern struct shape *plane(const struct coord*, const struct coord*);
extern struct shape *sphere(const struct coord*, double);
extern struct shape *paraboloid(const struct coord*, const struct coord*,
				double);
extern struct shape *cylinder(const struct coord*, const struct coord*, double);
extern struct shape *cone(const struct coord*, const struct coord*, double);

#endif /* SHAPE_H */
