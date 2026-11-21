# s-memalloc (Saptaparno's memory allocator)

An experimental memory allocator written in C. `s_malloc` is implemented; `s_free`, `s_calloc`, and `s_realloc` are still pending.

This project is for my learning of how programs request memory from the OS, how memory is tracked, and how to manage it efficiently.

---

## Design

First of all, this is roughly what the memory layout of a program looks like:

![memory layout](./docs/sketches/memory-layout.png)

The stack and the heap grow in opposite directions.

The current `s_malloc` implementation requests memory with `sbrk`, which moves the program break (the end of the process's data segment). It stores a header before each returned block and tracks those headers in a linked list. When an existing free block is large enough, `s_malloc` reuses it; otherwise, it requests a new block from `sbrk`.

The memory blocks are kept in a linked list so the allocator can traverse and find reusable blocks:

![memory block linked list](./docs/sketches/mem_block_linked_list.png)

`s_malloc` returns `NULL` for a zero-size request or if `sbrk` fails. Access to the allocator's block list is protected by a mutex. The other allocation functions and deallocation are not implemented yet.

---

## Author

Saptaparno Chakraborty

---
