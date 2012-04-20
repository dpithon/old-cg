/**
 * Basic pixmap package.
 *
 */

#ifndef _BPIX_CORE_H
#define _BPIX_CORE_H

typedef unsigned char cval; /* color component: from 0 to 255 */

struct bpix {
	int init;	/* magic value (0x696E6974 if struct is initialized) */
	int w, h;	/* width and height of pixmap                        */
	int stride;	/* row size in bytes, round to upper multiple of 4   */
	int sz;		/* size in bytes 				     */
	int int_sz;	/* size in word (4 bytes)			     */
	cval *data;	/* pointer to pixmap buffer			     */
	int error;	/* error value set by bpix function		     */
};

#define BPIX_MAX_W	8192
#define BPIX_MAX_H	8192

#define bpix_get_width(ptr)	((ptr)->w)
#define bpix_get_height(ptr)	((ptr)->h)

int bpix_init(struct bpix*, int, int);
int bpix_cleanup(struct bpix*);
int bpix_set(struct bpix*, int, int, cval, cval, cval);
int bpix_get(struct bpix*, int, int, cval*, cval*, cval*);

#endif /* _BPIX_CORE_H */
