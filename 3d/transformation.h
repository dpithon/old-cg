#ifndef _TRANSFORMATION_H
#define _TRANSFORMATION_H

extern union matrix *translation(union matrix*, float, float, float);
extern union matrix *rotation_x(union matrix*, float);
extern union matrix *rotation_y(union matrix*, float);
extern union matrix *rotation_z(union matrix*, float);
extern union matrix *scaling(union matrix*, float, float, float);

#endif /* _TRANSFORMATION_H */
