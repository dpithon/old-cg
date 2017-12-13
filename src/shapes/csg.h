#ifndef CSG_H
#define CSG_H

#include "treenode.h"

struct csg {
	struct treenode t;
};


#endif /* CSG_H */

/*
 * scene
 * - objects = object_list
 * - lights
 *
 * object_list:
 * - head: dlinked_object
 * - tail: dlinked_object
 *
 * dlinked_object:
 * - dlink
 * - object
 *
 * object
 * - object_kind_id
 * - object_def
 *
 * object_kind_id:
 *  - SPHERE|PLANE|CYLINDER_CONE|PARABOLOID|CSG
 *
 * object_def:
 * - surface_data
 * - solid_data
 * - csg = (operator_n, csg1_n, csg2_n) | solid
 */
