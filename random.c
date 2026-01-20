#include "random.h"

// PCG32 code / (c) 2014 M.E. O'Neill / pcg-random.org
// Licensed under Apache License 2.0 (NO WARRANTY, etc. see website)

static prng_state s_prng_state = {
    0x853c49e6748fea9bULL, 0xda3e39cb94b95bdbULL, NAN
};

void prng_seed_r(prng_state* rng, u64 initstate, u64 initseq){
    rng->state = 0U;
    rng->inc = (initseq << 1u) | 1u;
    prng_rand_r(rng);
    rng->state += initstate;
    prng_rand_r(rng);
    rng -> prev_norm = NAN;
}

void prng_seed(u64 initstate, u64 initseq){
    prng_seed_r(&s_prng_state, initstate, initseq);
}

u32 prng_rand_r(prng_state* rng){
    uint64_t oldstate = rng->state;
    rng->state = oldstate * 6364136223846793005ULL + rng->inc;
    uint32_t xorshifted = ((oldstate >> 18u) ^ oldstate) >> 27u;
    uint32_t rot = oldstate >> 59u;
    return (xorshifted >> rot) | (xorshifted << ((-rot) & 31));
}

u32 prng_rand(void){
    return prng_rand_r(&s_prng_state);
}

f32 prng_randf_r(prng_state*rng){
     return (f32) prng_rand_r(rng) / (f32)UINT32_MAX;
}

f32 prng_randf(){
    return prng_randf_r(&s_prng_state);
}

