#include <assert.h>
#include <stdio.h>
#include <math.h>

#include "log.h"
#include "pool.h"
#include "rgb.h"

static struct rgb def_rgb = Black;
static int pixmap_pool;
static unsigned char *data;
static int pix_width, pix_height, pix_size, pix_stride;


/** init_pixmap - initialize pixmap
 * 
 * w: width of pixmap
 * h: height of pixmap
 *
 * return 0 on success
 */
int init_pixmap(int w, int h)
{
	if (pix_size != 0)
		fatal("pixmap already initialized");

	if (w < 0 || h < 0)
		fatal("bad width or size");

	pix_width = w;
	pix_height = h;
	pix_size = pix_width * pix_height * 3;
	pix_stride = pix_width * 3;

	pixmap_pool = pool_init(pix_size);
	data = pool_alloc(pixmap_pool, pix_size);

	return 0;
}


int set_pixel(int x, int y, struct rgb *rgb)
{
	assert(x >= 0 && x < pix_width);
	assert(y >= 0 && y < pix_height);

	int offset = pix_stride * y + x * 3;

	if (!rgb)
		rgb = &def_rgb;

	data[offset]     = (unsigned char) roundf(255. * rgb->r);
	data[offset + 1] = (unsigned char) roundf(255. * rgb->g);
	data[offset + 2] = (unsigned char) roundf(255. * rgb->b);

	return 0;
}


int write_pixmap(const char *fname)
{
	FILE *fp;

	if (!(fp = fopen(fname, "w")))
		return error("failed to open file in write mode", 1);

	fprintf(fp, "P6\n# Created by Cg\n%d %d\n255\n", pix_width, pix_height);
	fwrite(data, pix_size, 1, fp);
	fclose(fp);

	return 0;
}


void release_pixmap(void)
{
	pool_free(pixmap_pool);
}


int pixmap_width(void)
{
	return pix_width;
}


int pixmap_height(void)
{
	return pix_height;
}
