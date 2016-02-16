#ifndef _SCENE_H
#define _SCENE_H

void location(const coord_t*);
void look_at(const coord_t*);

int  add_shape(const shape_t*);
/* int  add_light(const light_t*); */

bool init_scene(
bool intersect(ipoint_t*, const ray_t*);

#endif /* _SCENE_H */

#ifndef _SHAPE_H
#define _SHAPE_H

struct shape {
	ccs_t m;
	ccs_t mi;

	bool (*intersect)(ipoint_t*, const shape_t*, const ray_t*);
	void (*render)(rgb_t*, const ipoint_t*, 
	
#endif /* _SHAPE_H */

#ifndef _IPOINT_H
#define _IPOINT_H

#define FLAG_INSIDE	1
#define FLAG_OUTSIDE	2
#define FLAG_OVER	4
#define FLAG_UNDER	8

#define IS_INSIDE(i)	((i)->flags & FLAG_INSIDE)
#define IS_OUTSIDE(i)	((i)->flags & FLAG_OUTSIDE)
#define IS_OVER(i)	((i)->flags & FLAG_OVER)
#define IS_UNDER(i)	((i)->flags & FLAG_UNDER)

typedef struct ipoint {
	shape_t *shape;
	coord_t i;
	float   dist;
	int     flags;
} ipoint_t;

#endif /* _IPOINT_H */
