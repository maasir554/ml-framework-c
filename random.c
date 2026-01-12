#include<stdint.h>
#include<math.h>

// PCG32 code / (c) 2014 M.E. O'Neill / pcg-random.org
// Licensed under Apache License 2.0 (NO WARRANTY, etc. see website)

typedef uint32_t u32;
typedef uint64_t u64;
typedef float f32;

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

static prng_state s_prng_state = {
    0x853c49e6748fea9bULL, 0xda3e39cb94b95bdbULL, NAN
};

void prng_seed_r(prng_state* rng, u64 initstate, u64 initseq){
    rng->state = 0U;
    rng->inc = (initseq << 1u) | 1u;
    pcg32_random_r(rng);
    rng->state += initstate;
    pcg32_random_r(rng);
    rng -> prev_norm = NAN;
}

void prng_seed(u64 initstate, u64 initseq){
    pnr_seed_r(&s_prng_state, initstate, initseq);
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

// Box Muller Transformaton to get normalized values
f32 prng_rand_norm_r(prng_state* rng){
    if(!isnan(rng->prev_norm)){
        f32 out = rng -> prev_norm;
        rng -> prev_norm = NAN;
        return out;
    }
    f32 u1 = 1.0f, u2 = 0.0f;
    do{
        u1 = prng_randf_r(rng);
    }while(u1 == 0.0f);
    f32 u2 = rng_randf_r(rng);
    f32 mag = sqrt(-2.0f * logf(u1));
    f32 z0 = mag * cosf(2.0 * PI * u2);
    f32 z1 = mag * sinf(2.0 * PI * u2);

    rng -> prev_norm = z1; 

    return z0;
}

f32 prng_rand_norm(void){
    return prng_rand_norm_r(&s_prng_state);
}
