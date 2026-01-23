# Machine Learning Framework in C

## Development Note

1. Implements Arena Allocator: A better alternative for dynamic memory allocation as compared to `malloc` / `free` for this usecase.

2. Implements a Psuedo Random Number Generator (PRNG) to be used in ML calculatons.

[18 Jan 2025]
3. make the repository compiler ready: declare `include guards` in the header files

the code can be compiled using:

```bash
clang main.c arena.c random.c OS_MEMORY.c matrix.c -o main.out
```

[21 Jan 2025]
4. Matix multiplication on CPU with loop optimizations

5. for training model: Mnist dataset (handwritten digits)

# why is python used in this project?
- Python was used to extract the Mnist dataset from the tensorflow_datasets.
- the processed data files (.mat) is stored in  /datasets/output/*
- to generate the test and training data files do the following:

```bash
cd dataset
source .venv/bin/activate
python main.py
```