/**
 * Simple pixmap module.
 *
 */

#ifndef _GPIX_H
#define _GPIX_H

typedef unsigned char cval; /* color component: from 0 to 255 */

struct gpix {
	int w, h, stride;
	int sz, int_sz;
	cval *data;
	int error;
	cval fg_r, fg_g, fg_b;
	cval bg_r, bg_g, bg_b;
};

#define GPIX_MAX_W	8192
#define GPIX_MAX_H	8192

#define GPIX_DEF_W	800
#define GPIX_DEF_H	600

#define GPIX_INIT	{GPIX_DEF_W,GPIX_DEF_H,0,0,0,0,0,255,255,255,0,0,0}

#define gpix_width(ptr)		((ptr)->w)
#define gpix_height(ptr)	((ptr)->h)
#define gpix_stride(ptr)	((ptr)->stride)
#define gpix_data(ptr)		((ptr)->data)

int gpix_init(struct gpix*);
int gpix_cleanup(struct gpix*);
int gpix_set(struct gpix*, int, int, cval, cval, cval);
int gpix_get(struct gpix*, int, int, cval*, cval*, cval*);

#endif /* _GPIX_H */
