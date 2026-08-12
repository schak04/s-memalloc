/*
s-memalloc
Author: Saptaparno Chakraborty
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

struct header_t {
    size_t size;
    unsigned is_free;
};

void* s_malloc(size_t size) {
    void* mem_block;
    mem_block = sbrk(size);
    if (mem_block == (void*)-1) {
        return NULL;
    }
    return mem_block;
}

void s_free(void* _Nullable p);
