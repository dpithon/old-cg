#ifndef SHAPE_H
#define SHAPE_H

#include "types.h"
#include "vmath.h"

#define CAST_SHAPE(s)	((struct shape*)(s))
#define SHAPE_BASIC	struct shape *next;\
			struct cs cs;\
			struct matrix cam_to_shp;\
			struct matrix shp_to_cam;\
			void  *paint_data;\
			intersect_f intersect;\
			paint_f paint


struct shape {
	SHAPE_BASIC;
};


extern struct shape *plane(const struct coord*, const struct coord*);
extern struct shape *sphere(const struct coord*, double);
extern struct shape *paraboloid(const struct coord*, const struct coord*,
				double);
extern struct shape *cylinder(const struct coord*, const struct coord*, double);
extern struct shape *cone(const struct coord*, const struct coord*, double);

#endif /* SHAPE_H */
