#ifndef _TRANSFORM_H
#define _TRANSFORM_H

void t_id(void);
#define t_compound(type, ...)	_t_compound_##type(__VA_ARGS__)

int  t_push(void);
int  t_pop(void);

int  t_apply(coord_st*, coord_st*);
int  t_apply_rev(coord_st*, coord_st*);

int  _t_compound_ROT(float, float, float, float);
int  _t_compound_SCL(float, float, float);
int  _t_compound_SHR(float, float, float);
int  _t_compound_TSL(float, float, float);

#endif /* _TRANSFORM_H */
