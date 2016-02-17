#ifndef _SAMPLER_H
#define _SAMPLER_H

void set_sampler(void (*)(int, int));

extern void (*sampling)(int, int);

#endif /* _SAMPLER_H */
