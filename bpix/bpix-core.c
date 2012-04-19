#include <stdlib.h>
#include <assert.h>
#include "bpix-core.h"
#include "bpix-error.h"


int bpix_init(struct bpix *gp)
{
	assert(sizeof(int) == 4);

	if (gp->data) {
		gp->error = BPIX_ERR_ALREADY_INIT;
		return 1;
	}

	if (gp->w < 0 || gp->h < 0 || 
	    gp->w > BPIX_MAX_W || gp->h > BPIX_MAX_H) {
		gp->error = BPIX_ERR_PIXMAP_SIZE;
		return 1;
	}

	gp->stride = gp->w << 2;
	gp->sz = gp->stride * gp->h;
	gp->int_sz = gp->sz >> 2;

	gp->data = malloc(gp->sz);
	if (! gp->data) {
		gp->error = BPIX_ERR_MALLOC;
		return 1;
	}

	return 0;
}


/**
 * bpix_cleanup: release memory buffer and reset structure.
 */
int bpix_cleanup(struct bpix *gp)
{
	if (gp->data) {
		free(gp->data);
		gp->data = 0;

		gp->w = BPIX_DEF_W;
		gp->h = BPIX_DEF_H;
		gp->stride = gp->sz = gp->int_sz = 0;
		gp->fg_r = gp->fg_g = gp->fg_b = 255;
		gp->bg_r = gp->bg_g = gp->bg_b = 0;

		return 0;
	}

	gp->error = BPIX_ERR_ALREADY_FREE;
	return 1;
}


void bpix_fill(struct bpix *gp)
{
	int i, pix;

	pix = (gp->bg_r << 16) + (gp->bg_g << 8) + gp->bg_b;

	for (i = 0; i < gp->int_sz; i++) {
		gp->data[i] = pix;
	}
}


int bpix_set(struct bpix *gp, int x, int y, cval r, cval g, cval b)
{
	if (! gp->data) {
		gp->error = BPIX_ERR_UNINITIALIZED;
		return 1;
	}

	if (x < gp->w && x > -1 && y < gp->h && y > -1) {
		int offset = gp->stride * y + (x << 2);

		/* data[offset + 3] unused */
		gp->data[offset + 2] = r; 
		gp->data[offset + 1] = g; 
		gp->data[offset]     = b; 
		return 0;
	}

	gp->error = BPIX_ERR_OUTSIDE;
	return 1;
}


int bpix_get(struct bpix *gp, int x, int y, cval *r, cval *g, cval *b)
{
	if (! gp->data) {
		gp->error = BPIX_ERR_UNINITIALIZED;
		return 1;
	}

	if (x < gp->w && x > -1 && y < gp->h && y > -1) {
		unsigned int offset = gp->stride * y + (x << 2);

		*r = gp->data[offset + 2]; 
		*g = gp->data[offset + 1]; 
		*b = gp->data[offset]; 
		return 0;
	}

	gp->error = BPIX_ERR_OUTSIDE;
	return 1;
}
