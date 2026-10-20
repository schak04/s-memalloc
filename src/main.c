/*
s-memalloc: a simple memory allocator for learning memory management
Author: Saptaparno Chakraborty
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct mem_block_info mem_block_info;

// NOTE: sbrk is a system call that can be used to manipulate the program break `brk`
// - sbrk(0) gives the current address of the program break
// - sbrk(x) where x is positive, increments brk by x bytes -> allocates memory
// - sbrk(-x) where x is positive, decrements brk by x bytes -> releases memory
// - On failure, sbrk() returns `(void*) -1`
void* s_malloc(size_t size) {
    void* mem_block = sbrk(size);

    if (mem_block == (void*)-1) {
        return NULL;
    }

    return mem_block;
}

// NOTE: to free memory, the size of the block must be known
// so it needs to be stored somewhere
// plus, heap memory is contiguous -> it can only be stretched and
// shrunk at one end, so freeing memory != releasing memory
// a freed block can simply be marked as free and reused later

// NOTE: every memory block needs to store 2 things:
// 1. size, and 2. whether it is free or not
// this info is stored in a header hidden from the calling program
/*
 +---------------------------------+
 |            |                    |
 |  header    |   Actual memory    |
 |            |      block         |
 |            |                    |
 +---------------------------------+
*/

// NOTE: when a program requests 'size' bytes of memory,
// total_size = header_size + size -> call sbrk(total_size)

struct mem_block_info {
    size_t size;
    unsigned is_free;
    struct mem_block_info* next;
};

// NOTE: a linked list to be used to keep track of the memory blocks
// allocated by s_malloc, so freed blocks can be found and reused

// TODO: continue from here

void s_free(void* _Nullable p) {}
