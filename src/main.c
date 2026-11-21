/*
s-memalloc: a simple memory allocator for learning memory management
Author: Saptaparno Chakraborty
*/

#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// NOTE: x-byte alignment: the object's starting address must be a multiple of x

// ensures the memory block header is aligned to 16 bytes
typedef char MEM_BLOCK_INFO_ALIGNER[16];

typedef union mem_block_info {
    struct {
        size_t size;
        bool is_free;
        union mem_block_info* next;
    } payload;

    MEM_BLOCK_INFO_ALIGNER aligner;
} mem_block_info;

mem_block_info *head, *tail;

// shared state: head & tail, the linked list of memory block headers, each memory block's metadata

pthread_mutex_t s_malloc_lock = PTHREAD_MUTEX_INITIALIZER;

mem_block_info* scan_and_fetch_free_block(size_t size) {
    mem_block_info* curr = head;

    while (curr) {
        if (curr->payload.is_free && curr->payload.size >= size) {
            return curr;
        }
        curr = curr->payload.next;
    }

    return NULL;
}

// NOTE:
// sbrk(0) -> current address of the program break (brk)
// sbrk(x) increments brk by x bytes
// sbrk(-x) decrements brk by x bytes
// failure -> (void*) -1

// a linked list of (memory block + its metadata)s store the allocated memory blocks

void* s_malloc(size_t size) {
    if (!size) return NULL;

    size_t size_to_be_allocated;
    void* mem_block;
    mem_block_info* info;

    // protect shared allocator state from concurrent modifications
    pthread_mutex_lock(&s_malloc_lock);

    // search and reserve a free block while holding the lock to prevent
    // multiple threads from claiming the same block
    info = scan_and_fetch_free_block(size);

    if (info) {
        info->payload.is_free = false;
        pthread_mutex_unlock(&s_malloc_lock);
        return (void*)(info + 1);  // the block whose details 'info' carries
    }

    // no suitable free block exists so request additional heap memory

    size_to_be_allocated = sizeof(mem_block_info) + size;
    mem_block = sbrk(size_to_be_allocated);

    if (mem_block == (void*)-1) {  // sbrk failure
        pthread_mutex_unlock(&s_malloc_lock);
        return NULL;
    }

    // set new mem_block's metadata
    info = mem_block;
    info->payload.size = size;
    info->payload.is_free = false;
    info->payload.next = NULL;

    if (!head) {
        head = info;
        tail = info;
    } else {
        tail->payload.next = info;
        tail = info;
    }

    pthread_mutex_unlock(&s_malloc_lock);

    return (void*)(info + 1);
}

void s_free(void* _Nullable p) {}
