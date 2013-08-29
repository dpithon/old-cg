#ifndef _VMATH_IO_H
#define _VMATH_IO_H

extern char *coord_to_str(char*, int, int*, char, const coord_st*);
extern char *matrix_to_str(char*, int, int*, const matrix_st*);
extern char *mstack_to_str(char*, int, int*, const mstack_st*);

extern void print_coord(char*, const coord_st*);
extern void print_matrix(char*, const matrix_st*);
extern void print_mstack(char*, const mstack_st*);

extern void print_vstat(vstat_st*);

extern int dump_coord(char*,  int, int*, char, const coord_st*);
extern int dump_matrix(char*, int, int*, const matrix_st*);
extern int dump_mstack(char*,  int, int*, const mstack_st*);
extern int dump_vstat(char*,  int, int*, const vstat_st*);
extern int load_coord(coord_st*,   const char*, int, int*);
extern int load_matrix(matrix_st*, const char*, int, int*);
extern int load_mstack(mstack_st*,  const char*, int, int*);
extern int load_vstat(vstat_st*,  const char*, int, int*);


#endif /* _VMATH_IO_H */
