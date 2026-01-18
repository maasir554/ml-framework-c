#ifndef BASE_H
#define BASE_H

#include<stdio.h>
#include<stdint.h>
#include<string.h>
#include<stdbool.h>

// short form for commonly used types
typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef float f32;

typedef i8 b8;
typedef i32 b32;

// the actual arena structure
typedef struct{ 
    u64 reserve_size, commit_size, pos, commit_pos;
} mem_arena;

// type agnostic minimum and maximum
#define MIN(a, b) (((a)<(b)) ? (a) : (b))
#define MAX(a, b) (((a)>(b)) ? (a) : (b))

// get how many Bytes in the bigger units like KiB, MiB, GiB
#define KiB(n) ((u64)(n) << 10)
#define MiB(n) ((u64)(n) << 20)
#define GiB(n) ((u64)(n) << 30)
#define ALIGN_UP_POWER_2(n, p) (((u64)(n) + (u64)(p) - 1)&(~((u64)(p)-1)))

#endif // BASE_H