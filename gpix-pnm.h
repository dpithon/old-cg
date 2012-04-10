/**
 * pnm input/output module for gpix
  */

#ifndef _GPIX_PNM_H
#define _GPIX_PNM_H

#include "gpix.h"

int gpix_pnm_write_to_file(struct gpix*, const char*);
int gpix_pnm_read_from_file(struct gpix*, const char*);

#endif /* _GPIX_PNM_H */
