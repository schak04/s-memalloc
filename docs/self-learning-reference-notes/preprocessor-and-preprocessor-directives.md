# Preprocessor

Preprocessors are programs that process the source code before the actual compilation begins.
They are not part of the compilation process but operate separately,
allowing programmers to modify the code before compilation.

## Flow:

```
Source code -> Preprocessor --(preprocessed file .i)--> Compiler --(assembly code .s)--> Assembler --(object code .o)--> Linker --(executable)--> Output
```

## Types of Preprocessors (in C):

1. Macros
2. File inclusion
3. Conditional compilation
4. Others (like `#pragma`)

> [!NOTE]  
> `#pragma`:  
> Provides specific instructions to the compiler to control its behaviour. It is used to disable warnings, set alignment, etc.

---

## Preprocessor Directives

These are the commands that we give to the preprocessor.

They always start with `#`.

---