#ifndef LOG_H
#define LOG_H

extern void fatal(const char*);
extern int  error(const char*, int);
extern void warning(const char*);
extern void info(const char*);

#ifndef NDEBUG
#define debug(m)		 debug_(m)
extern void debug_(const char*);
#else  /* ! NDEBUG */
#include "macros.h"
#define debug(m)		 NOOP
#endif /* ! NDEBUG */

#endif /* LOG_H */
