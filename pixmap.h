/**
 * Basic pixmap package.
 *
 */

#ifndef PIXMAP_H
#define PIXMAP_H

#include "types.h"

typedef unsigned char cval; /* color component: from 0 to 255 */

#define BPIX_MAX_W	8192
#define BPIX_MAX_H	8192

#define bpix_get_width(ptr)	((ptr)->w)
#define bpix_get_height(ptr)	((ptr)->h)

int bpix_init(struct bpix*, int, int);
int bpix_cleanup(struct bpix*);
int bpix_set(struct bpix*, int, int, cval, cval, cval);
int bpix_get(struct bpix*, int, int, cval*, cval*, cval*);

int bpix_pnm_write_to_file(struct bpix*, const char*);

#endif /* PIXMAP_H */
