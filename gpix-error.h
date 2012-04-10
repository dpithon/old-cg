#ifndef _GPIX_ERROR_H
#define _GPIX_ERROR_H

extern const char *GPIX_ERRSTR[];

#define gpix_error(ptr)		((ptr)->error)
#define gpix_errstr(ptr)	(GPIX_ERRSTR[((ptr)->error)])

#define GPIX_ERR_NONE			  0

/* gpix errors */
#define GPIX_ERR_ALREADY_INIT		  1
#define GPIX_ERR_PIXMAP_SIZE		  2
#define GPIX_ERR_MALLOC			  3
#define GPIX_ERR_ALREADY_FREE		  4
#define GPIX_ERR_UNINITIALIZED		  5
#define GPIX_ERR_OUTSIDE		  6

/* gpix-cairo errors */
#define GPIX_ERR_GPIX_TO_CAIRO_FAILURE	 20 
#define GPIX_ERR_CAIRO_TO_GPIX_FAILURE	 21 

/* gpix-pnm errors */
#define GPIX_ERR_IO			 30

#endif /* _GPIX_ERROR_H */
