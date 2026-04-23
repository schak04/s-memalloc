# Memory Layout of a Program

> The memory layout of a program shows how its data is stored in memory during execution.

A process runs within its own virtual address space that’s distinct from the virtual address spaces of other processes.  
This virtual address space typically comprises of these parts:  
- **Text Segment**: _stores the executable code of the program like program’s functions and instructions_
- **Data Segment**: _stores global and static variables of the program_
    - **Initialised Data Segment**: _contains non-zero global and static variables that have been initialised by the programmer_
    - **Uninitialised Data Segment** (BSS / Block Started by Symbol): _This contains zero-initialised static data. If uninitialised, automatically initialised to zero by the system at runtime._
- **Heap**: _used for dynamic memory allocation_
- **Stack**: _stores local variables, function parameters, and return addresses for each function call_

---

## More Info

- The stack and the heap grow in the opposite directions.
- Sometimes, initialised vars + bss (uninitialised vars) + heap segment = data segment
    - End of this segment is marked off by a pointer named "program break" or `brk`.
    - Hence, `brk` points to the end of the heap.