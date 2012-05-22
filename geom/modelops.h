#ifndef _MODELOPS_H
#define _MODELOPS_H

union matrix;

extern void model_push(void);
extern void model_pop(void);
extern void model_load_id(void);
extern void model_translate(float, float, float);
extern void model_scale(float, float, float);
extern void model_rotate_x(float);
extern void model_rotate_y(float);
extern void model_rotate_z(float);
extern void model_multiply(const union matrix*);

#endif /* _MODELOPS_H */