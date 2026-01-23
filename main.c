#include "base.h"
#include "arena.h"
#include "random.h"
#include "matrix.h"

void print_mnist_digit(f32* data){
    for(u32 y = 0; y < 28; y += 1){
        for(u32 x = 0; x < 28; x += 1){
            f32 val = data[y*28 + x];
            u32 intensity = 232 + (u32)(val*24);
            printf("\x1b[48;5;%dm  ", intensity);
        }
        printf("\x1b[0m\n");
    }
}

int main(void){
    mem_arena* perm_arena = arena_create(GiB(1), MiB(1));
    
    matrix* train_images = mat_load(perm_arena, 60000, 784, "./dataset/output/train_images.mat");
    matrix* test_images = mat_load(perm_arena, 10000, 784, "./dataset/output/test_images.mat");
    
    matrix* train_labels = mat_create(perm_arena, 60000, 10);
    matrix* test_labels = mat_create(perm_arena, 10000, 10);
    // scope for loading the the probability distribution (Manhattan Coding)
    {
        matrix* train_labels_file = mat_load(perm_arena, 60000, 1, "./dataset/output/train_labels.mat");
        matrix* test_labels_file = mat_load(perm_arena, 10000, 1, "./dataset/output/test_labels.mat");
        
        for(u32 i = 0; i < 60000; i += 1){
            u32 pos = train_labels_file->data[i];
            train_labels->data[10*i + pos] = 1.0f;
        }
        
        for(u32 i = 0; i < 10000; i += 1){
            u32 pos = test_labels_file->data[i];
            test_labels->data[10*i + pos] = 1.0f;
        }
    }

    print_mnist_digit(train_images->data + 5*784);
    for(u32 i = 0; i < 10; i += 1){
        printf("%.0f ", train_labels->data[50 + i]);
    }
    printf("\n");
    arena_destroy(perm_arena);
    return 0;
}
