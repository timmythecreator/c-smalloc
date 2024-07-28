# smalloc

smalloc is a simple memory allocator implemented in C.

It provides custom implementations for `malloc()`, `calloc()`, `realloc()`, and `free()`, allowing for manual management of dynamic memory allocation in C programs.

## Features

- **malloc()**: Allocates a block of memory of a specified size.
- **calloc()**: Allocates an array of blocks, initializing all bytes to zero.
- **realloc()**: Resizes a previously allocated block of memory.
- **free()**: Frees a previously allocated block of memory, making it available for future allocations.

## Compile and Run

To compile `smalloc`, you can use the following command:

```bash
gcc -o smalloc.so -fPIC -shared smalloc.c
```

- `fPIC`: Generates position-independent code (PIC), which is a requirement for creating shared libraries.
- `shared`: Produces a shared object which can be loaded dynamically.

## Using `smalloc` as a Shared Library

With `LD_PRELOAD` set, any subsequent commands run in the same shell session will use smalloc for memory allocation. For example:

```bash
ls
vim somefile.txt
```

You can also run your own programs with `smalloc` to test its functionality.

## Stopping the Use of `smalloc`

To stop using `smalloc`, simply unset the `LD_PRELOAD` environment variable:

```bash
unset LD_PRELOAD
```

This will revert to the system's default memory allocation functions.

## Note

This project is intended for educational purposes and to demonstrate the basics of implementing a memory allocator. 
It is not optimized for production use and may not handle all edge cases or provide the same level of safety and efficiency as standard memory allocators.
