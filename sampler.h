#ifndef SAMPLER_H
#define SAMPLER_H

typedef void (*sampler)(int, int);

void set_sampler(sampler);

extern sampler sampling;

#endif /* SAMPLER_H */
