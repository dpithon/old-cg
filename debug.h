#ifndef DEBUG_H
#define DEBUG_H

#include "types.h"

extern void fatal(const char*);
extern void warning(const char*);
extern int  error(const char*, int);
extern void print_matrix(const char*, const struct matrix*);
extern void print_coord(const char*, const struct coord*);

#ifndef NDEBUG

#define debug(m)		 debug_(m)
#define assert_is_mequal(m1, m2) assert__is_mequal(m1, m2, __LINE__, __FILE__)
#define assert_is_vector(c)	 assert__is_vector(c, __LINE__, __FILE__)
#define assert_is_point(c)	 assert__is_point(c, __LINE__, __FILE__)
#define assert_is_not_vzero(c)   assert__is_not_vzero(c, __LINE__, __FILE__)
#define assert_is_vunit(c)	 assert__is_vunit(c, __LINE__, __FILE__)
#define assert_is_cartesian_coord_system(i, j, k)\
		assert__is_cartesian_coord_system(i, j, k, __LINE__, __FILE__)


extern void debug_(const char*);
extern void assert__is_mequal(const struct matrix*, const struct matrix*,
			      int, char*);
extern void assert__is_vector(const struct coord*, int, char*);
extern void assert__is_point(const struct coord*, int, char*);
extern void assert__is_not_vzero(const struct coord*, int, char*);
extern void assert__is_vunit(const struct coord*, int, char*);
extern void assert__is_cartesian_coord_system(const struct coord*,
				       const struct coord*,
				       const struct coord*,
				       int, char*);

#else  /* ! NDEBUG */
#define NOOP ((void)0)

#define debug(m)		 NOOP
#define assert_is_mequal(m1, m2) NOOP
#define assert_is_vector(c)	 NOOP
#define assert_is_point(c)	 NOOP
#define assert_is_not_vzero(c)   NOOP
#define assert_is_vunit(c)	 NOOP
#define assert_is_cartesian_coord_system(i, j, k) NOOP

#endif /* ! NDEBUG */

#endif /* DEBUG_H */
