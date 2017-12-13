#ifndef MACROS_H
#define MACROS_H

#define NOOP		((void)0)
#define SORT(a, b)	if (a > b) { __typeof__(a) t; t = a; a = b; b = t; }

#define CONCAT(a, b)		a ## b
#define CONCAT_(a, b)		CONCAT(a, b)
#define UNIQUE_NAME(base)	CONCAT_(base, __LINE__)

#endif /* MACROS_H */
