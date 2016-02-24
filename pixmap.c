#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "pixmap.h"
#include "log.h"


static struct {
	int w, h;    /* width and height of pixmap */
	int sz;	     /* size in bytes 		   */
	cval *data;  /* pointer to pixmap buffer   */
} bp;


int pixmap_init(int w, int h)
{
	if (w < 0 || h < 0)
		return 1;

	bp.w = w;
	bp.h = h;

	bp.data = malloc(w * h * 3);
	if (! bp.data)
		return 1;

	return 0;
}


int pixmap_cleanup(void)
{
	if (bp.data) {
		free(bp.data);
		bp.data = (cval*) 0;
	}
	return 0;
}


int pixmap_set(int x, int y, cval r, cval g, cval b)
{
	int offset = bp.w * y * 3 + x * 3;

	bp.data[offset]     = r; 
	bp.data[offset + 1] = g; 
	bp.data[offset + 2] = b; 

	return 0;
}


int pixmap_get(int x, int y, cval *r, cval *g, cval *b)
{
	int offset = bp.w * y * 3 + x * 3;

	*r = bp.data[offset]; 
	*g = bp.data[offset + 1]; 
	*b = bp.data[offset + 2]; 

	return 0;
}


static int write_ppm(const char *fname)
{
	FILE *fp;

	if (!(fp = fopen(fname, "w")))
		return 1;

	fprintf(fp, "P6\n# Created by Cg\n%d %d\n255\n", bp.w, bp.h);
	fwrite(bp.data, bp.w * bp.h * 3, 1, fp);
	fclose(fp);

	return 0;
}


int pixmap_write(int fmt, const char *fname)
{
	switch (fmt) {
	case FORMAT_PPM:
		return write_ppm(fname);
	default:
		warning("unknown file format (default to ppm)");
		return write_ppm(fname);
	}
}
	

