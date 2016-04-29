#ifndef MACROS_H
#define MACROS_H

#define NOOP		((void)0)
#define SORT(a, b)	if (a > b) { __typeof__(a) t; t = a; a = b; b = t; }

#endif /* MACROS_H */
