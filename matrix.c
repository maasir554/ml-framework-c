#include "matrix.h"


// Matrix Utility functions: 

matrix* mat_create(mem_arena* arena, u32 rows, u32 cols){
    matrix* mat = PUSH_STRUCT(arena, matrix);
    mat -> rows = rows;
    mat -> cols = cols;
    mat -> data = PUSH_ARRAY(arena, matrix, (u64)rows * cols);

    return mat;
}

b32 mat_copy(matrix* dst, matrix* src){
    if(dst -> rows != src -> rows || dst -> cols != src -> cols) return false;
    memcpy(dst->data, src->data, sizeof(f32)*(u64)src->rows*src->cols);
    
    return true; 
}

void mat_clear(matrix* mat){
    memset(mat, 0, sizeof(f32) * (u64)mat->rows * mat->cols);
}

void mat_fill(matrix* mat, f32 val){
    u64 size = (u64)mat->rows * mat->cols;
    for(u64 i = 0; i < size; i += 1) mat->data[i] = val;
}

void mat_scale(matrix* mat, f32 scale){
    u64 size = (u64)mat->rows * mat->cols;
    // for(u64 i = 0; i < size; i += 1) (mat->data)[i] *= scale;
    for(u64 i = 0; i < size; i += 1) *(mat->data + i) *= scale; // the commneted above line can be used instead of this.
}

// Actual matirx arithmatic functions:


