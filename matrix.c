#include "matrix.h"

// Matrix Utility functions: 

matrix* mat_create(mem_arena* arena, u32 rows, u32 cols){
    // ROW MAJOR index access is assumned wherever applicable
    matrix* mat = PUSH_STRUCT(arena, matrix);
    mat -> rows = rows;
    mat -> cols = cols;
    mat -> data = PUSH_ARRAY(arena, f32, (u64)rows * cols);

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

f32 mat_sum(const matrix* mat){
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

// _mat_mul_<is `a` transpose><is `b` transpose>
// n -> not transpose, t -> transpose
void _mat_mul_nn(matrix*out, const matrix*a, const matrix*b){
    for(u32 i = 0; i < a->rows; i += 1){
        for(u32 k = 0; k < b->cols; k += 1){
            for(u32 j = 0; j < a->cols; j += 1){
                // out[i][k] += a[i][j] * b[j][k]
                out->data[i * b->cols + k] += 
                    a->data[i * a->cols + j] * b->data[j * b->cols + k];
            }
        }
    }
}

void _mat_mul_nt(matrix*out, const matrix*a, const matrix*b){
    // b is transposed: b'[j][k] = b[k][j]
    for(u32 i = 0; i < a->rows; i += 1){
        for(u32 k = 0; k < b->rows; k += 1){  // b transposed: cols become rows
            for(u32 j = 0; j < a->cols; j += 1){
                // out[i][k] += a[i][j] * b'[j][k] = a[i][j] * b[k][j]
                out->data[i * b->rows + k] += 
                    a->data[i * a->cols + j] * b->data[k * b->cols + j];
            }
        }
    }
}

void _mat_mul_tn(matrix*out, const matrix*a, const matrix*b){
    // a is transposed: a'[i][j] = a[j][i]
    for(u32 j = 0; j < a->rows; j += 1){  // a transposed: cols become rows
        for(u32 i = 0; i < a->cols; i += 1){  // a transposed: rows become cols
            for(u32 k = 0; k < b->cols; k += 1){
                // out[i][k] += a'[i][j] * b[j][k] = a[j][i] * b[j][k]
                out->data[i * b->cols + k] += 
                    a->data[j * a->cols + i] * b->data[j * b->cols + k];
            }
        }
    }
}

void _mat_mul_tt(matrix*out, const matrix*a, const matrix*b){
    // both transposed
    for(u32 i = 0; i < a->cols; i += 1){
        for(u32 j = 0; j < a->rows; j += 1){
            for(u32 k = 0; k < b->rows; k += 1){
                // out[i][k] += a'[i][j] * b'[j][k] = a[j][i] * b[k][j]
                out->data[i * b->rows + k] += 
                    a->data[j * a->cols + i] * b->data[k * b->cols + j];
            }
        }
    }
}

// the nested ordering of i, j, k loops can affect performance by 2 to 10 times
// optimal scheme: the (A*ROWS + B) expression works best if B is inner most
// and A(strided) should be higher in the order
// reason: memory access paterns and cache

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

    u32 transpose_config = (transpose_a << 1) | transpose_b;

    switch(transpose_config){
        case 0b00: _mat_mul_nn(out, a, b); break;
        case 0b01: _mat_mul_nt(out, a, b); break;
        case 0b10: _mat_mul_tn(out, a, b); break;
        case 0b11: _mat_mul_tt(out, a, b); break;
    }

    return true;
}

b32 mat_relu(matrix* out, const matrix* in){
    if(out->rows != in->rows || out->cols != in->cols) return false;
    u64 size = (u64)in->rows * in->cols;
    for(u64 i = 0; i < size; i += 1) out->data[i] = MAX(in->data[i], 0);
    return true;
}

// Softmax Function (Neural Network Activation):
// FORMULA: SoftMax(a[i]) = e^(a[i]) / sum(e^(a[i]) form 0 to n)

b32 mat_softmax(matrix* out, const matrix* in){
    if(out->rows != in->rows || out->cols != in->cols) return false;
    u64 size = (u64) in->rows * in->cols;
    f32 smm = 0.0f;
    for(u64 i = 0; i < size; i += 1){
        out->data[i] = expf(in->data[i]);
        smm += out->data[i];
    }
    mat_scale(out, 1.0f / smm);
    return true;
}

// cross entropy calculation of matrix p and q
b32 mat_cross_entropy(matrix* out, const matrix* p, const matrix* q){
    if(out->rows != p->rows || out->cols != p->cols) return false;
    if(out->rows != q->rows || out->cols != q->cols) return false;
    u64 size = (u64)out->rows * out->cols;
    // cross entropy(p,q) = sum(-p[i]*log(q[i]))
    // for this function, we will not cumpute the sum, but compute the terms instead
    for(u64 i = 0; i < size; i += 1) 
        out->data[i] = -p->data[i] * (q->data[i] == 0.0f ? 0.0f: 
        logf(q->data[i]));
    
    return true;
}

matrix* mat_load(mem_arena* arena, u32 rows, u32 cols, char* filename){
    matrix* mat = mat_create(arena, rows, cols);
    FILE* f = fopen(filename, "rb");
    if(!f) return NULL;

    u64 size = (u64)rows * cols;
    fread(mat->data, sizeof(f32), size, f);
    fclose(f);
    return mat;
}
