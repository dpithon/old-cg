#ifndef _SHAPE_H
#define _SHAPE_H

struct shape {
	ccs_t m;
	ccs_t mi;

	bool (*intersect)(ipoint_t*, const shape_t*, const ray_t*);
	void (*render)(rgb_t*, const ipoint_t*, 
	
#endif /* _SHAPE_H */
