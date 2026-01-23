#include "base.h"
#include "arena.h"
#include "random.h"
#include "matrix.h"

int main(void){
    mem_arena* perm_arena = arena_create(GiB(1), MiB(1));
    
    matrix* train_images = mat_load(perm_arena, 60000, 784, "./dataset/output/train_images.mat");
    matrix* test_images = mat_load(perm_arena, 10000, 784, "./dataset/output/test_images.mat");
    printf("Working all OK\n");
    arena_destroy(perm_arena);
    return 0;
}
