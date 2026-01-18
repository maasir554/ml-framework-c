#ifndef RANDOM_H
#define RANDOM_H

#include "base.h"

typedef struct { 
    u64 state, inc; 
    f32 prev_norm;
} prng_state;

#define PI 3.14159265358979

void prng_seed_r(prng_state* rng, u64 initstate, u64 initseq);
void prng_seed(u64 initstate, u64 initseq);

u32 prng_rand_r(prng_state* rng);
u32 prng_rand(void);

f32 prng_randf_r(prng_state* rng);
f32 prng_randf(void);

f32 prng_rand_norm_r(prng_state* rng);
f32 prng_rand_norm(void);

#endif // RANDOM_H