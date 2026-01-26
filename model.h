#ifndef MODEL_H
#define MODEL_H
#include "base.h"
#include "matrix.h"

typedef enum {
    MV_FLAG_NONE = 0,

    MV_FLAG_REQUIRES_GRAD   = (1<<0),
    MV_FLAG_PARAMETER       = (1<<1),
    MV_FLAG_INPUT           = (1<<2),
    MV_FLAG_OUTPUT          = (1<<3),
    MV_FLAG_DESIRED_OUUTPUT = (1<<4),
    MV_FLAG_COST            = (1<<5)
} model_var_flags;

typedef enum { 
    MV_OP_NULL = 0,
    MV_OP_CREATE,
    _MV_OP_UNARY_START,
    
    MV_OP_RELU,
    MV_OP_SOFTMAX,
    _MV_OP_BINARY_START,

    MV_OP_ADD,
    MV_OP_SUN,
    MV_OP_MATMUL,
    MV_OP_CROSS_ENTROPY,
} model_var_ops;

typedef struct{
    u32 num_vars;
    matrix* input;
    matrix* output;
    matrix* desired_output;
    matrix* cost;
} model_context;

#define MODEL_VAR_MAX_INPUTS 2
#define MV_NUM_INPUTS(op) ( (op) < _MV_OP_UNARY_START ? 0 : (op) < _MV_OP_BINARY_START ? 1 : 2 )

typedef struct {
    u32 index, flags;
    matrix *val, *grad;
} model_var;

#endif