# s-memalloc

A small C memory allocator project for learning how dynamic memory is requested, tracked, and reused. It provides `s_malloc`, `s_free`, `s_calloc`, and `s_realloc` as learning implementations of the familiar allocation functions.

## Current scope

I've implemented all four functions with some behaviours intentionally kept simple. `s_malloc` returns `NULL` for a zero-size request and `s_calloc` checks for multiplication overflow. `s_realloc` allocates a new block when growing, copies the old contents, and frees the old block; it returns the existing block when the requested size fits. Shrinking a block in place is not implemented yet.

This is a hobby/learning project.

## Design

Each allocation has a metadata header (`mem_block_info`) immediately before its usable memory. Metadata are linked together so the allocator can search for memory blocks to reuse. `s_malloc` uses a first-fit search: it takes the first free block that is large enough, or asks for more memory with `sbrk` if none is available.

Freed blocks that are not at the end of the heap are marked free for later reuse. If the freed block is at the end, `s_free` moves the program break backwards to return that memory. Blocks are not split or merged. A mutex protects the allocator's shared block list while `s_malloc` and `s_free` update it.

The allocator's use of `sbrk` is the central part of this project: it makes the relationship between allocation metadata, the heap, and the program break visible.

## Diagrams

The first sketch shows the process memory layout:

![Memory layout](./docs/sketches/memory-layout.png)

The second is to visualise the linked list of the memory blocks' metadata:

![Memory block linked list](./docs/sketches/mem_block_linked_list.png)

## Author

Saptaparno Chakraborty
