#include <float.h>
#include "ipoint.h"

void reset_ipoint(struct ipoint *i)
{
	i->flags = 0;
	i->k = FLT_MAX;
}


void set_ipoint(struct ipoint *i, const struct shape *shp, int flg, float k)
{
	i->shape = shp;
	i->flags = FLAG_DEFINED|flg;
	i->k     = k;
}
