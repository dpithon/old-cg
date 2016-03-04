#ifndef LOG_H
#define LOG_H

#include "types.h"

void fatal(const char*);
void warning(const char*);

#ifndef NDEBUG
void assert_is_mequal(const struct matrix*, const struct matrix*);

#else  /* ! NDEBUG */

#define assert_is_mequal(m1, m2) ((void)0)((void)0)
#endif /* ! NDEBUG */

#endif /* LOG_H */
