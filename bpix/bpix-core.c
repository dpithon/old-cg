#include <stdlib.h>
#include <assert.h>
#include "bpix-core.h"
#include "bpix-error.h"


int bpix_init(struct bpix *bp, int w, int h)
{
	assert(sizeof(int) == 4);
	assert(bp->init != 0x696E6974);

	if (w < 0 || h < 0 || w > BPIX_MAX_W || h > BPIX_MAX_H) {
		bp->errno = BPIX_ERR_PIXMAP_SIZE;
		return 1;
	}

	bp->w = w;
	bp->h = h;
	bp->stride = w << 2;
	bp->sz = bp->stride * h;

	bp->data = calloc(bp->sz >> 2, 4);
	if (! bp->data) {
		bp->errno = BPIX_ERR_MALLOC;
		return 1;
	}

	bp->init = 0x696E6974;
	bp->errno = 0;

	return 0;
}


/**
 * bpix_cleanup: release memory buffer and reset structure.
 */
int bpix_cleanup(struct bpix *bp)
{
	assert(bp->init == 0x696E6974);

	free(bp->data);
	bp->init = 0;

	return 0;
}


int bpix_set(struct bpix *bp, int x, int y, cval r, cval g, cval b)
{
	assert(bp->init == 0x696E6974);

	if (x < bp->w && x > -1 && y < bp->h && y > -1) {
		int offset = bp->stride * y + (x << 2);

		/* data[offset + 3] unused */
		bp->data[offset + 2] = r; 
		bp->data[offset + 1] = g; 
		bp->data[offset]     = b; 
		return 0;
	}

	bp->errno = BPIX_ERR_OUTSIDE;
	return 1;
}


int bpix_get(struct bpix *bp, int x, int y, cval *r, cval *g, cval *b)
{
	assert(bp->init == 0x696E6974);

	if (x < bp->w && x > -1 && y < bp->h && y > -1) {
		unsigned int offset = bp->stride * y + (x << 2);

		*r = bp->data[offset + 2]; 
		*g = bp->data[offset + 1]; 
		*b = bp->data[offset]; 
		return 0;
	}

	bp->errno = BPIX_ERR_OUTSIDE;
	return 1;
}
