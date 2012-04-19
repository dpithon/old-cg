#ifndef _BPIX_ERROR_H
#define _BPIX_ERROR_H

extern const char *BPIX_ERRSTR[];

#define bpix_error(ptr)		((ptr)->error)
#define bpix_errstr(ptr)	(BPIX_ERRSTR[((ptr)->error)])

#define BPIX_ERR_NONE			  0

/* bpix errors */
#define BPIX_ERR_ALREADY_INIT		  1
#define BPIX_ERR_PIXMAP_SIZE		  2
#define BPIX_ERR_MALLOC			  3
#define BPIX_ERR_ALREADY_FREE		  4
#define BPIX_ERR_UNINITIALIZED		  5
#define BPIX_ERR_OUTSIDE		  6

/* bpix-cairo errors */
#define BPIX_ERR_BPIX_TO_CAIRO_FAILURE	 20 
#define BPIX_ERR_CAIRO_TO_BPIX_FAILURE	 21 

/* bpix-pnm errors */
#define BPIX_ERR_IO			 30

/* bpix-gtk errors */
#define BPIX_ERR_GTK			 40

#define BPIX_ERR_MAX			 BPIX_ERR_GTK

#endif /* _BPIX_ERROR_H */
