/**
 * Simple pixmap module.
 *
 */

#ifndef _BPIX_CORE_H
#define _BPIX_CORE_H

typedef unsigned char cval; /* color component: from 0 to 255 */

struct bpix {
	int w, h, stride;
	int sz, int_sz;
	cval *data;
	int error;
	cval fg_r, fg_g, fg_b;
	cval bg_r, bg_g, bg_b;
};

#define BPIX_MAX_W	8192
#define BPIX_MAX_H	8192

#define BPIX_DEF_W	800
#define BPIX_DEF_H	600

#define BPIX_INIT	{BPIX_DEF_W,BPIX_DEF_H,0,0,0,0,0,255,255,255,0,0,0}

#define bpix_width(ptr)		((ptr)->w)
#define bpix_height(ptr)	((ptr)->h)
#define bpix_stride(ptr)	((ptr)->stride)
#define bpix_data(ptr)		((ptr)->data)

int bpix_init(struct bpix*);
int bpix_cleanup(struct bpix*);
int bpix_set(struct bpix*, int, int, cval, cval, cval);
int bpix_get(struct bpix*, int, int, cval*, cval*, cval*);

#endif /* _BPIX_CORE_H */
