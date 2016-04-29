#ifndef SURFPROP_H
#define SURFPROP_H

#include "vmath.h"

#define CAST_SURFPROP(s)	((struct surfprop*)(s))
#define SURFPROP_BASIC		struct coord_system *cs

struct surfprop {
	SURFPROP_BASIC;
};

#endif /* SURFPROP_H */
