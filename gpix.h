/**
 * Simple pixmap module.
 *
 * Create a pixmap with direct access to raw pixels plus basic
 * raster graphic functions.
 *
 */

#ifndef _GPIX_H
#define _GPIX_H

typedef unsigned char cval; /* color component: from 0 to 255 */

struct gpix {
	int w, h, stride, error;
	int sz, int_sz;
	cval *data;
	cval fg_r, fg_g, fg_b, fg_a;
	cval bg_r, bg_g, bg_b, bg_a;
};

#define GPIX_INIT		{800, 600, 3200, 0, 0, 255, 255, 255, 0, 0, 0}

#define gpix_width(ptr)		((ptr)->w)
#define gpix_height(ptr)	((ptr)->h)
#define gpix_stride(ptr)	((ptr)->stride)
#define gpix_data(ptr)		((ptr)->data)
#define gpix_error(ptr)		((ptr)->error)
#define gpix_errstr(ptr)	(GPIX_ERRSTR[((ptr)->error)])

extern const char *GPIX_ERRSTR[];

int gpix_create(struct gpix*);
int gpix_destroy(struct gpix*);

int gpix_set(struct gpix*, int, int, cval, cval, cval);
int gpix_get(struct gpix*, int, int, cval*, cval*, cval*);

void gpix_line(struct gpix*, int, int, int, int);

#endif /* _GPIX_H */
