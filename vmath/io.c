#include <stdio.h>

#define _VMATH_INTERNALS

#include "core.h"
#include "mstack.h"
#include "mstack.p"
#include "stat.h"
#include "stat.p"
#include "io.h"
#include "settings.p"

static int dump_mm(char*, int, int*, const void*, int, char);
static int load_mm(const char*, int, int*, void*, int);
static void printfmt(char*, char*);

#if __BYTE_ORDER__ != __ORDER_LITTLE_ENDIAN__
#error "Unsupported byte order."
#endif

#define MATROW(m, i) ((coord_st*) &(m->cell[i]))

char *coord_to_str(char *buf, int sz, int *of, char z, const coord_st *c)
{
        int rsz;

        if (vmset_start_char) {
                rsz = snprintf(
                        &(buf[*of]), (sz - *of), 
                        "%c %*.*f %*.*f %*.*f %*.*f%c",
                        vmset_start_char,
                        vmset_width, vmset_prec, c->x, 
                        vmset_width, vmset_prec, c->y,
                        vmset_width, vmset_prec, c->z, 
                        vmset_width, vmset_prec, c->w, z
                );
        } else {
                rsz = snprintf(
                        &(buf[*of]), (sz - *of), 
                        "%*.*f %*.*f %*.*f %*.*f%c",
                        vmset_width, vmset_prec, c->x, 
                        vmset_width, vmset_prec, c->y,
                        vmset_width, vmset_prec, c->z, 
                        vmset_width, vmset_prec, c->w, z
                );
        }

        if (rsz >= (sz - *of)) {
                return NULL;
        }

	*of += rsz;

        return buf;
}


char *matrix_to_str(char *buf, int sz, int *of, const matrix_st *m)
{
        for (int i = 0; i < 4;  i++) {
                if (! coord_to_str(buf, sz, of, '\n', MATROW(m, i))) {
                        return NULL;
                }
        }

        return buf;
}


char *mstack_to_str(char *buf, int sz, int *of, const mstack_st *s)
{
	if (! s) {
		s = &vmath_mstack;
	}

        int i = s->i;
        while (i >= 0) {
                if (! matrix_to_str(buf, sz, of, &(s->m[i--]))) {
                        return NULL;
                }
		if (sz - *of >= 2) {
			buf[(*of)++] = '\n';
			buf[*of] = '\0';
		} else {
			return NULL;
		}
        }

	return buf;
}


void print_coord(char *fmt, const coord_st *c)
{
	static char buf[80];
	int i = 0;

	printfmt(fmt, coord_to_str(buf, 80, &i, 0, c));
}


void print_matrix(char *fmt, const matrix_st *m)
{
	static char buf[320];
	int i = 0;

	printfmt(fmt, matrix_to_str(buf, 320, &i, m));
}


void print_mstack(char *fmt, const mstack_st *s)
{
	static char buf[5120];
	int i = 0;

	printfmt(fmt, mstack_to_str(buf, 5120, &i, s));
}




#ifdef VSTAT
/**
 * print_vstat: output detailed statistics
 *
 * stat: pointer to a vstat structure (0 means current stats)
 */
void print_vstat(vstat_st *stat)
{
        uint32_t *ul;

        if (! stat) {
                stat = &vmath_stat;
        }

        ul = (uint32_t*) stat;

        for (int i = 0; vstat_str[i]; i++) {
                printf("%6d ..... %s\n", ul[i], vstat_str[i]);
        }
}
#endif /* VSTAT */



/**
 * dump_coord: convert coordinates (4 float values) in hex string
 *
 * Values are separated with space.
 *
 * buf: pointer to buffer
 * sz : buffer size
 * of : pointer to start offset in buffer
 * z  : final char to output into buffer
 * c  : pointer to coordinates
 * 
 * Returns: 
 *   0: ok
 *   1: buffer overflow
 *
 */
int dump_coord(char *buf, int sz, int *of, char z, const coord_st *c)
{
        float *f = (float*) c;

        for (int err, i = 0; i < 4; i++) {
                if ((err = dump_mm(buf, sz, of, &f[i], 4, (i == 3)? z: ' '))) {
                        return 1;
                }
        }

        return 0;
}


/**
 * dump_matrix: convert matrix (16 float values) in hex string
 *
 * buf: pointer to buffer
 * sz : buffer size
 * of : pointer to start offset in buffer
 * m  : pointer to matrix
 * 
 * Returns: 
 *   0: ok
 *   1: buffer overflow
 *
 */
int dump_matrix(char *buf, int sz, int *of, const matrix_st *m)
{
        for (int err, i = 0; i < 4;  i++) {
                if ((err = dump_coord(buf, sz, of, '\n', MATROW(m, i)))) {
                        return err;
                }
        }

        return 0;
}


/**
 * dump_stack: convert stack in hex string
 *
 * buf: pointer to buffer (0 means main matrix stack)
 * sz : buffer size
 * of : pointer to start offset in buffer
 * s  : pointer to stack
 * 
 * Returns: 
 *   0: ok
 *   1: buffer overflow
 *
 */
int dump_mstack(char *buf, int sz, int *of, const mstack_st *s)
{
        if (! s) {
                s = (const mstack_st*) &vmath_mstack;
        }

        if (dump_mm(buf, sz, of, &(s->i), sizeof s->i, '\n')) {
		return 1;
	}

        for (int err, i = s->i; i >= 0; i--) {
                if ((err = dump_matrix(buf, sz, of, &(s->m[i])))) {
                        return 1;
                }
        }

        return 0;
}


/**
 * dump_stat: convert stat in hex string
 *
 * buf: pointer to buffer (0 means main matrix stack)
 * sz : buffer size
 * of : pointer to start offset in buffer
 * s  : pointer to stat
 * 
 * Returns: 
 *   0: ok
 *   1: buffer overflow
 *
 */
int dump_vstat(char *buf, int sz, int *of, const vstat_st *s)
{
        uint32_t *ul;
	char sp;

        if (! s) {
                ul = (uint32_t*) &vmath_stat;
        } else {
                ul = (uint32_t*) s;
	}

        for (int err, i = 0; vstat_str[i]; i++) {
		sp = ((i % 5) == 4) ? '\n': ' '; 
		if ((err = dump_mm(buf, sz, of, &(ul[i]), 4, sp))) {
                        return err;
                }
        }

	buf[*of - 1] = '\n';
        return 0;
}


int load_coord(coord_st *c, const char *buf, int sz, int *of)
{
        float *f = (float*) c;

        for (int err, i = 0; i < 4; i++) {
                if ((err = load_mm(buf, sz, of, &f[i], sizeof *f))) {
                        return err;
                }
                (*of)++;
        }

        return 0;
}


int load_matrix(matrix_st *m, const char *buf, int sz, int *of)
{
        for (int err, i = 0; i < 4;  i++) {
                if ((err = load_coord(MATROW(m, i), buf, sz, of))) {
                        return err;
                }
        }

        return 0;
}


int load_mstack(mstack_st* s, const char *buf, int sz, int *of)
{
	int err;

        if (! s) {
                s = (mstack_st*) &vmath_mstack;
        }

        if ((err = load_mm(buf, sz, of, &(s->i), sizeof s->i))) {
		return err;
	}

        (*of) ++;
        for (int i = s->i; i >= 0; i--) {
                if ((err = load_matrix(&(s->m[i]), buf, sz, of))) {
                        return err;
                }
        }

        return 0;
}


int load_vstat(vstat_st* s, const char *buf, int sz, int *of)
{
	uint32_t *ul;

        if (! s) {
                ul = (uint32_t*) &vmath_stat;
        } else {
                ul = (uint32_t*) s;
	}

        for (int err, i = 0; vstat_str[i]; i++) {
		if ((err = load_mm(buf, sz, of, &(ul[i]), 4))) {
                        return err;
                }
                (*of)++;
        }

        return 0;
}


/**
 * dump_mm: dump memory area to hex codes
 *
 * buf: pointer to buffer
 * bsz: buffer size
 * of : pointer to start offset in buffer
 * mm : pointer to first byte of memory area
 * sz : size of memory area (in bytes)
 * z  : final char to output into buffer
 * 
 * Returns: 
 *   0: ok
 *   1: buffer overflow
 *
 */

int dump_mm(char *buf, int bsz, int *of, const void *mm, int sz, char z)
{
        static char hexa[] = { 
                '0', '1', '2', '3', '4', '5', '6', '7',
                '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'
        };
        const unsigned char *uc = (const unsigned char*) mm;
        unsigned char b;

        for (int i = 0; i < sz; i++) {
                if (bsz - *of < 4) {
                        return 1;
                }

                b = uc[sz - 1 - i];
                buf[(*of)++] = hexa[b >> 4];
                buf[(*of)++] = hexa[b & 0x0F];
        }

        buf[(*of)++] = z;
        buf[*of] = '\0';

        return 0;
}


static unsigned char decode_hex(char c)
{
        if (c >= '0' && c <= '9')
                return c - '0';
        else if (c >= 'A' && c <= 'F')
                return 10 + (c - 'A');
        else
                return 16;
}


/**
 * load_mm: decode hex codes to memory
 *
 * buf: pointer to buffer
 * bsz: buffer size
 * of : pointer to start offset in buffer
 * mm : pointer to first byte of memory area
 * sz : size of memory area to feed (in bytes)
 * 
 * Returns: 
 *   0: ok
 *   1: buffer overflow
 *   2: not an hex character
 *
 */
int load_mm(const char *buf, int bsz, int *of, void *mm, int sz)
{
        unsigned char *uc = (unsigned char*) mm;
        unsigned char hi, lo;

        for (int i = sz - 1; i >= 0; i--) {
                if (bsz - *of < 2) {
                        return 1;
                }

                // decode two HEX characters in a byte
                hi = decode_hex(buf[(*of)++]);
                lo = decode_hex(buf[(*of)++]);
                if (hi > 15 || lo > 15)
                        return 2;

                uc[i]  = hi << 4;
                uc[i] += lo;
        }

        return 0;
}



static void printfmt(char *fmt, char *str)
{
	printf(fmt, str);
}
