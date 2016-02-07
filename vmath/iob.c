#if __BYTE_ORDER__ != __ORDER_LITTLE_ENDIAN__
#error "Unsupported byte order."
#endif

#define _VMATH_INTERNALS

#include <stdio.h>
#include "core.h"
#include "mstack.h"
#include "mstack.p"
#include "stat.h"
#include "stat.p"
#include "iob.h"
#include "settings.p"

static char *dump_coord_hex(vmiob_t *iob, const coord_t *c);
static char *dump_coord_asc(vmiob_t *iob, const coord_t *c);
static int dump_mm(vmiob_t*, const void*, int);
static int load_mm(vmiob_t*, void*, int);
static unsigned char decode_hex(char);


char *dump_coord(vmiob_t *iob, const coord_t *c)
{
	switch (iob->fmt) {
	case VMIOB_ASC:
		return dump_coord_asc(iob, c);
	case VMIOB_HEX:
		return dump_coord_hex(iob, c);
	default:
		iob->err = VMIOB_ERR_FMT;
		return NULL;
	}
}



char *dump_matrix(vmiob_t *iob, const matrix_t *m)
{
        for (int i = 0; i < 4;  i++) {
                if (! dump_coord(iob, MATROW(m, i))) {
                        return NULL;
		}
		iob->buf[iob->of - 1] = '\n';
		
	}

        return iob->buf;
}


char *dump_mstack(vmiob_t *iob, const mstack_t *s)
{
	if (! s) {
		s = (const mstack_t*) &vmath_mstack;
	}

	if (iob->fmt == VMIOB_HEX) {
		if (dump_mm(iob, &(s->i), sizeof s->i)) {
			return NULL;
		}
		iob->buf[iob->of - 1] = '\n';
	}

        for (int i = s->i; i >= 0; i--) {
                if (! dump_matrix(iob, &(s->m[i]))) {
                        return NULL;
                }
		if (iob->sz - iob->of >= 2) {
			iob->buf[(iob->of)++] = '\n';
			iob->buf[iob->of]     = '\0';
		} else {
			iob->err = VMIOB_ERR_OVR;
			return NULL;
		}
        }

        return iob->buf;
}


#ifdef VSTAT
char *dump_vstat(vmiob_t *iob, const vstat_t *s)
{
	uint32_t *ul;

        if (! s) {
                ul = (uint32_t*) &vmath_stat;
        } else {
                ul = (uint32_t*) s;
	}

        for (int i = 0; vstat_tr[i]; i++) {
		if (dump_mm(iob, &(ul[i]), 4)) {
                        return NULL;
                }

		if (i % 5 == 4) 
			iob->buf[iob->of - 1] = '\n';
        }

	iob->buf[iob->of - 1] = '\n';
        return iob->buf;
}
#endif /* VSTAT */




int load_coord(coord_t *c, vmiob_t *iob)
{
        float *f = (float*) c;

        for (int i = 0; i < 4; i++) {
                if (load_mm(iob, &f[i], sizeof *f)) {
                        return iob->err;
                }
                (iob->of)++;
        }

        return 0;
}


int load_matrix(matrix_t *m, vmiob_t *iob)
{
        for (int i = 0; i < 4;  i++) {
                if (load_coord(MATROW(m, i), iob)) {
                        return iob->err;
                }
        }

        return 0;
}


int load_mstack(mstack_t* s, vmiob_t *iob)
{
        if (! s) {
                s = (mstack_t*) &vmath_mstack;
        }

        if (load_mm(iob, &(s->i), sizeof s->i)) {
		return iob->err;
	}

        (iob->of) ++;
        for (int i = s->i; i >= 0; i--) {
                if (load_matrix(&(s->m[i]), iob)) {
                        return iob->err;
                }
		iob->of ++;
        }

        return 0;
}


#ifdef VSTAT
int load_vstat(vstat_t* s, vmiob_t *iob)
{
	uint32_t *ul;

        if (! s) {
                ul = (uint32_t*) &vmath_stat;
        } else {
                ul = (uint32_t*) s;
	}

        for (int i = 0; vstat_tr[i]; i++) {
		if (load_mm(iob, &(ul[i]), 4)) {
                        return iob->err;
                }
                (iob->of)++;
        }

        return 0;
}
#endif /* VSTAT */


/***************************************************************************/


static unsigned char decode_hex(char c)
{
        if (c >= '0' && c <= '9')
                return c - '0';
        else if (c >= 'A' && c <= 'F')
                return 10 + (c - 'A');
        else
                return 16; /* 16 means: error! */
}


static int dump_mm(vmiob_t *iob, const void *mm, int sz)
{
        static char hexa[] = { 
                '0', '1', '2', '3', '4', '5', '6', '7',
                '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'
        };
        const unsigned char *uc = (const unsigned char*) mm;
        unsigned char b;

        for (int i = 0; i < sz; i++) {
                if (iob->sz - iob->of < 4) {
                        return VMIOB_ERR_OVR;
                }

                b = uc[sz - 1 - i];
                iob->buf[(iob->of)++] = hexa[b >> 4];
                iob->buf[(iob->of)++] = hexa[b & 0x0F];
        }

        iob->buf[(iob->of)++] = ' ';
        iob->buf[iob->of] = '\0';

        return 0;
}


static int load_mm(vmiob_t *iob, void *mm, int sz)
{
        unsigned char *uc = (unsigned char*) mm;
        unsigned char hi, lo;

        for (int i = sz - 1; i >= 0; i--) {
                if (iob->sz - iob->of < 2)
                        return VMIOB_ERR_OVR;

                // decode two HEX characters in a byte
                hi = decode_hex(iob->buf[(iob->of)++]);
                lo = decode_hex(iob->buf[(iob->of)++]);
                if (hi > 15 || lo > 15) {
			iob->err = VMIOB_ERR_CNV;
			break;
		} else {
			uc[i]  = hi << 4;
			uc[i] += lo;
		}
        }

        return iob->err;
}



static char *dump_coord_asc(vmiob_t *iob, const coord_t *c)
{
        int rsz, max = iob->sz - iob->of;
	char *start = &(iob->buf[iob->of]);

        if (vmset_start_char) {
                rsz = snprintf(
			start , max,
                        "%c %*.*f %*.*f %*.*f %*.*f",
                        vmset_start_char,
                        vmset_width, vmset_prec, c->x, 
                        vmset_width, vmset_prec, c->y,
                        vmset_width, vmset_prec, c->z, 
                        vmset_width, vmset_prec, c->w
                );
        } else {
                rsz = snprintf(
			start , max,
                        "%*.*f %*.*f %*.*f %*.*f",
                        vmset_width, vmset_prec, c->x, 
                        vmset_width, vmset_prec, c->y,
                        vmset_width, vmset_prec, c->z, 
                        vmset_width, vmset_prec, c->w
                );
        }

        if (rsz >= max) {
                return NULL;
        }

	iob->of += rsz;

        return iob->buf;
}


static char *dump_coord_hex(vmiob_t *iob, const coord_t *c)
{
        float *f = (float*) c;

        for (int i = 0; i < 4; i++) {
                if (dump_mm(iob, &f[i], sizeof(float))) {
                        return NULL;
                }
        }

        return iob->buf;
}
