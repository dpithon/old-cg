#ifndef STACK_H
#define STACK_H

extern void translate(double, double, double);
extern void rotate_x(double);
extern void rotate_y(double);
extern void rotate_z(double);
extern void pop(void);
extern void reset(void);
extern void transform(struct coord*);

#endif /* STACK_H */
