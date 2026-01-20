#include "matrix.h"


// Matrix Utility functions: 

matrix* mat_create(mem_arena* arena, u32 rows, u32 cols){
    // ROW MAJOR index access is assumned wherever applicable
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

f32 mat_sum(matrix* mat){
    u64 size = (u64)mat->rows * mat->cols;
    f32 smm = 0.0f;
    for(u64 i = 0; i < size; i += 1) smm += mat->data [i];
    
    return smm;
}

// Actual matirx arithmatic functions:

b32 mat_add(matrix* out, const matrix* a, const matrix* b){
    if(a->rows != b->rows || a->cols != b->cols) return false;
    if(out->rows != a->rows || out->cols != a->cols) return false;

    u64 size = (u64)a->rows * a->cols;
    for(u64 i = 0; i < size; i += 1) out->data [i] = a->data [i] + b->data [i];

    return true;
}

b32 mat_sub(matrix* out, const matrix* a, const matrix* b){
    if(a->rows != b->rows || a->cols != b->cols) return false;
    if(out->rows != a->rows || out->cols != a->cols) return false;

    u64 size = (u64)a->rows * a->cols;
    for(u64 i = 0; i < size; i += 1) out->data [i] = a->data [i] - b->data [i];

    return true;
}

b32 mat_mul(
    matrix* out, const matrix* a, const matrix* b, 
    b8 zero_out, b8 transpose_a, b8 transpose_b
){
    
    u32 rows_a = transpose_a ? a->cols : a->rows;
    u32 cols_a = transpose_a ? a->rows : a->cols;

    u32 rows_b = transpose_b ? b->cols : b->rows;
    u32 cols_b = transpose_b ? b->rows : b->cols;

    if(cols_a != rows_b) return false;
    if(out->rows != rows_a || out->cols != cols_b) return false;
    
    if(zero_out) mat_clear(out);
    // to be completed
    return true;
}

