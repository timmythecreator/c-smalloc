# Malloc and Arena Libraries

This project contains two custom memory allocator libraries implemented in C: `malloc` and `arena`. These libraries provide custom memory management functions and are designed to replace the standard memory allocation routines in C for educational purposes.

## Features

### Malloc library

- `smalloc(size_t size)`: Allocates a block of memory of the specified size.
- `scalloc(size_t num, size_t nsize)`: Allocates an array of blocks, initializing all bytes to zero.
- `srealloc(void *block, size_t size)`: Resizes a previously allocated block of memory.
- `sfree(void *block)`: Frees a previously allocated block of memory, making it available for future allocations.

### Arena Library
- `arena_init(size_t capacity)`: Initializes an arena with a given capacity.
- `arena_alloc(size_t size)`: Allocates memory from the arena.
- `arena_realloc(void *old_ptr, size_t old_size, size_t new_size)`: Reallocates memory within the arena.
- `arena_reset()`: Resets the arena, making all memory available for allocation again.
- `arena_free()`: Frees the memory used by the arena.

## Overview

### Previous Implementation

The initial implementation of this library used the `sbrk` function for memory allocation on Unix-like systems. However, `sbrk` is considered outdated and not recommended for modern applications, as it is not thread-safe and can lead to fragmentation and other issues.

### Current Implementation

The new version of this library uses `mmap` on Unix-like systems and `VirtualAlloc` on Windows for memory allocation. These methods provide better control over memory management and are more suitable for modern multi-threaded environments.

In addition, the `arena` library is introduced to provide a simple arena allocator, allowing for fast allocation and deallocation of memory in bulk. It uses the `malloc` library internally for its memory management.

## Building the Library

### On Unix-like Systems

To compile and create a shared library (`.so`), run:

```bash
./build_lib.sh
```

This will generate `libmalloc.so` and `libarena.so`.

### On Windows

To compile and create a shared library (.dll), run:

```cmd
build_lib.cmd
```
This will generate `malloc.dll` and `arena.dll`.

## Using the Library

### On Unix-like Systems

1. Set the `LD_LIBRARY_PATH` environment variable to include the directory where `libmalloc.so` and `arena.so` are located:

```bash
export LD_LIBRARY_PATH=/path/to/directory
```

2. Compile your program that uses the libraries:

```bash
gcc -o myprogram myprogram.c -L/path/to/directory -larena -lmalloc
```

3. Run your program:

```bash
./myprogram
```

### On Windows

1. Ensure `malloc.dll` and `arena.dll` are in the same directory as your executable or in a directory included in the system `PATH`.

2. Compile your program that uses the library:

```bash
gcc -o myprogram.exe myprogram.c -L/path/to/directory -larena -lmalloc
```

3. Run your program:

```bash
myprogram.exe
```

## Building and Running `test.c`

### On Unix-like Systems

1. Build the test program using:

```bash
./build_test.sh
```

2. Run the test program:

```bash
./test
```

### On Windows

1. Build the test.exe program using:

```cmd
build_test.cmd
```

2. Run the test.exe program:

```cmd
test.exe
```

## Example Usage

Here is a simple example program (`test.c`) that uses both the `malloc` and `arena` libraries:

```c
#include <stdio.h>
#include "malloc.h"
#include "arena.h"

int main() {
    // Example of using malloc
    void *ptr1 = smalloc(100);
    if (ptr1 == NULL) {
        printf("malloc failed\n");
        return 1;
    }
    printf("smalloc: allocated 100 bytes at %p\n", ptr1);
    sfree(ptr1);

    // Example of using arena
    arena_init(1024);
    void *arena_ptr = arena_alloc(100);
    if (arena_ptr == NULL) {
        printf("arena_alloc failed\n");
        return 1;
    }
    printf("arena_alloc: allocated 100 bytes at %p\n", arena_ptr);
    arena_free();

    return 0;
}
```

1. Compile the example using the provided build scripts (`build_test.sh` or `build_test.cmd`).

2. Run the compiled program (`test` or `test.exe`).

## Note

This project is intended for educational purposes and to demonstrate the basics of implementing a memory allocator. 
It is not optimized for production use and may not handle all edge cases or provide the same level of safety and efficiency as standard memory allocators.
