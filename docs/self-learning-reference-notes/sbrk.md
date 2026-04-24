# sbrk()

## What is it?

A system call that can be used in Linux or Unix-like systems to manipulate the program break, `brk`.

## Argument(s) it takes

- sbrk(0) gives the current address of the program break.
- sbrk(x) where x is positive, increments brk by x bytes -> allocates memory.
- sbrk(-x) with where x is positive (so -x will be negative), decrements brk by x bytes -> releases memory.
- On failure, sbrk() returns `(void*) -1`.

## Is it still used? Is it safe?

Yes, it is still used in malloc for small memory allocation, and otherwise `malloc` uses `mmap()`. And no, `sbrk()` is not thread safe, and `mmap()` is a modern and better alternative to it.
`sbrk()` can only grow or shrink in Last In First Out order.

But I'll use `sbrk()` for now, and will integrate `mmap` later, to enhance my learnings.

---