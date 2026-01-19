# Machine Learning Framework in C

## Development Note

1. Implements Arena Allocator: A better alternative for dynamic memory allocation as compared to `malloc` / `free` for this usecase.

2. Implements a Psuedo Random Number Generator (PRNG) to be used in ML calculatons.

[18 Jan 2025]
3. make the repository compiler ready: declare `include guards` in the header files

the code can be compiled using:

```bash
clang main.c arena.c random.c OS_MEMORY.c -o main.out
```
