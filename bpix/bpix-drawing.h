#ifndef _BPIX_DRAWING_H
#define _BPIX_DRAWING_H

#include "bpix-core.h"

struct gctx {
	cval fg_r, fg_g, fg_b;
	cval bg_r, bg_g, bg_b;
};

void bpix_line(struct bpix*, struct gctx*, int, int, int, int);

#endif /* _BPIX_DRAWING_H */
