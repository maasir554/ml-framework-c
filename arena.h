#ifndef ARENA_H
#define ARENA_H

#include "base.h"

// Power aligned to powers of two for faster access by CPU
#define ARENA_BASE_POS (sizeof(mem_arena))
#define ARENA_ALIGN (sizeof(void*))

// Actual Arena memory allocating and de-allicating funcions 
mem_arena* arena_create(u64 reserve_size, u64 commit_size);
void arena_destroy(mem_arena* arena);
void* arena_push(mem_arena* arena, u64 size, b32 non_zero);
void arena_pop(mem_arena* arena, u64 size);
void arena_pop_to(mem_arena* arena, u64 pos);
void arena_clear(mem_arena* arena);

// helper functions that interface Operating System.
u32 plat_get_pagesize(void);
void* plat_mem_reserve(u64 size);
b32 plat_mem_commit(void* ptr, u64 size);
b32 plat_mem_decommit(void* ptr, u64 size);
b32 plat_mem_release(void* ptr, u64 size);

// Utility macros to be used in applications.
#define PUSH_STRUCT(arena, T) (T*)arena_push((arena), sizeof(T), false)
#define PUSH_STRUCT_NZ(arena, T) (T*)arena_push((arena), sizeof(T), true)
#define PUSH_ARRAY(arena, T, n) (T*)arena_push((arena), sizeof(T)*(n), false)
#define PUSH_ARRAY_NZ(arena, T, n) (T*)arena_push((arena), sizeof(T)*(n), true)

#endif // ARENA_H
