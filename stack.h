#ifndef STACK_H
#define STACK_H

void translate(double, double, double);
void rotate_x(double);
void rotate_y(double);
void rotate_z(double);

void pop(void);
void reset(void);

void transform(struct coord*);

#endif /* STACK_H */
