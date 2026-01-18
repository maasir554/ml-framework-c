#include "base.h"
#include "arena.h"
#include "random.h"

int main(void){
    mem_arena* perm_arena = arena_create(GiB(1), MiB(1));
    
    arena_destroy(perm_arena);
    return 0;
}