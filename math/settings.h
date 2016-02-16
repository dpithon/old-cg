#ifndef _VMATH_SETTINGS_H
#define _VMATH_SETTINGS_H

#define VMSET_CAST(v)	((void*)v)

#define VMSET_EPSILON		1
#define VMSET_IO_WIDTH		2
#define VMSET_IO_PREC		3
#define VMSET_IO_START_CHAR	4

extern int vmath_set(int, void*);
extern int vmath_get(int, void*);

#endif /* _VMATH_SETTINGS_H */
