/*
s-memalloc: a simple memory allocator for learning memory management
Author: Saptaparno Chakraborty
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// to free memory, the size of the block must be known
// so it needs to be stored somewhere
// plus, heap memory is contiguous -> it can only be stretched and
// shrunk at one end, so freeing memory != releasing memory
// a freed block can simply be marked as free and reused later

// every memory block needs to store 2 things:
// 1. size, and 2. whether it is free or not
// this info is stored in a header hidden from the calling program
/*
+----------------------------+
|          |                 |
|  header  |  Actual memory  |
|          |     block       |
|          |                 |
+----------------------------+
*/

// a linked list is to be used to keep track of the memory blocks
// allocated by s_malloc, so freed blocks can be found and reused

// NOTE:
// 16-byte size: the object occupies 16 bytes
// 16-byte alignment: the object's starting address must be a multiple of 16

// ensures the memory block header is aligned to 16 bytes
typedef char MEM_BLOCK_INFO_ALIGNER[16];

typedef union mem_block_info {
    struct {
        size_t size;
        unsigned is_free;
        union mem_block_info* next;
    } mem_block_info;

    MEM_BLOCK_INFO_ALIGNER aligner;
} mem_block_info;

// NOTE:
// sbrk(0) -> current address of the program break (brk)
// sbrk(x) increments brk by x bytes
// sbrk(-x) decrements brk by x bytes
// failure -> (void*) -1

void* s_malloc(size_t size) {
    if (!size) return NULL;

    // 'size' bytes of memory needed -> sbrk(total_size)
    // total_size = header_size + size
    size_t total_size;
    void* mem_block;
    mem_block_info* info;

    if (mem_block == (void*)-1) {
        return NULL;
    }

    return mem_block;
}

void s_free(void* _Nullable p) {}
