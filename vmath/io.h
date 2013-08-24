#ifndef _VMATH_IO_H
#define _VMATH_IO_H

extern void printc(const char*, coord_st*);
extern void printm(const char*, matrix_st*);
extern void prints(const char*, mstack_st*);
extern void print_counters(counter_st*);

extern int dump_coord(char*,  int, int*, char, const coord_st*);
extern int dump_matrix(char*, int, int*, const matrix_st*);
extern int dump_stack(char*,  int, int*, const mstack_st*);

extern int load_coord(const char*, int, int*, coord_st*);
extern int load_matrix(const char*, int, int*, matrix_st*);
extern int load_stack(const char*, int, int*, mstack_st*);

extern int dump_counters(char*, int, const counter_st*);

#endif /* _VMATH_IO_H */
