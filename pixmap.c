#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "pixmap.h"
#include "rgb.h"
#include "log.h"

static struct rgb def_rgb = Black;


static struct {
	int w, h;    /* width and height of pixmap */
	int sz;	     /* size in bytes 		   */
	unsigned char *data;  /* pointer to pixmap buffer   */
} bp;


/** init_pixmap - initialize pixmap
 * 
 * w: width of pixmap
 * h: height of pixmap
 *
 * return 0 on success
 */
int init_pixmap(int w, int h)
{
	debug("entering init_pixmap");

	if (w < 0 || h < 0)
		return error("bad width or size", 1);

	bp.w = w;
	bp.h = h;

	bp.data = malloc(w * h * 3);
	if (! bp.data)
		return error("failed to allocate memory", 2);

	return 0;
}


int set_pixel(int x, int y, struct rgb *rgb)
{
	assert(x >= 0 && x < bp.w);
	assert(y >= 0 && y < bp.h);

	int offset = bp.w * y * 3 + x * 3;

	if (!rgb)
		rgb = &def_rgb;

	bp.data[offset]     = (unsigned char) roundf(255. * rgb->r);
	bp.data[offset + 1] = (unsigned char) roundf(255. * rgb->g);
	bp.data[offset + 2] = (unsigned char) roundf(255. * rgb->b);

	return 0;
}


static int write_ppm(const char *fname)
{
	FILE *fp;

	debug("entering write_ppm");

	if (!(fp = fopen(fname, "w")))
		return error("failed to open file in write mode", 1);

	fprintf(fp, "P6\n# Created by Cg\n%d %d\n255\n", bp.w, bp.h);
	fwrite(bp.data, bp.w * bp.h * 3, 1, fp);
	fclose(fp);

	return 0;
}


int write_pixmap(int fmt, const char *fname)
{
	switch (fmt) {
	case FORMAT_PPM:
		return write_ppm(fname);
	default:
		warning("unknown file format (default to ppm)");
		return write_ppm(fname);
	}
}
