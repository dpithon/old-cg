#include <stdio.h>
#include <bpix/bpix.h>

int main()
{
	int x, y;
	struct bpix bp;

	/* Create a 320x240 pixmap (max size is BPIX_MAX_W x BPIX_MAX_H) */
	if ( bpix_init(&bp, 320, 240) ) {
		fprintf(stderr, "bpix error: %s\n", bpix_get_errstr(&bp));
		return 1;
	}

	/* Draw a red box */
	for (x = 10; x < 100; x++)
		for (y = 10; y < 100; y++)
			bpix_set(&bp, x, y, 255, 0, 0);

	/* Wrong (x, y) values return error */
	if ( bpix_set(&bp, 2500, 13240, 0, 0, 0) ) {
		fprintf(stderr, "bpix error: %s\n", bpix_get_errstr(&bp));
		bpix_reset_errno(&bp); /* reset error field if program resume */
	} 
		
	/* Save pixmap in "red.pnm" file and free pixmap memory */
	if ( bpix_pnm_write_to_file(&bp, "red.pnm") || 
	     bpix_cleanup(&bp) ) {
		fprintf(stderr, "bpix error: %s\n", bpix_get_errstr(&bp));
		return 1;
	}

	/* bp could be safely reused: bpix_init(&bp, 640, 480); ... */
		
	return 0;
}
