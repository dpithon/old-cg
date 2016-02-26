#ifndef STACK_H
#define STACK_H

void translate(float, float, float);
void rotate_x(float);
void rotate_y(float);
void rotate_z(float);

void pop(void);
void reset(void);

void transform(struct coord*);

#endif /* STACK_H */
