# Malloc Library

Malloc is a simple custom memory allocator library implemented in C. It provides implementations for the standard memory management functions `malloc()`, `calloc()`, `realloc()`, and `free()`. This library can be used as a replacement for the standard memory allocation routines in C.

## Features

- **malloc(size_t size)**: Allocates a block of memory of the specified size.
- **calloc(size_t num, size_t nsize)**: Allocates an array of blocks, initializing all bytes to zero.
- **realloc(void *block, size_t size)**: Resizes a previously allocated block of memory.
- **free(void *block)**: Frees a previously allocated block of memory, making it available for future allocations.

## Overview

### Previous Implementation

The initial implementation of this library used the `sbrk` function for memory allocation on Unix-like systems. However, `sbrk` is considered outdated and not recommended for modern applications, as it is not thread-safe and can lead to fragmentation and other issues.

### Current Implementation

The new version of this library uses `mmap` on Unix-like systems and `VirtualAlloc` on Windows for memory allocation. These methods provide better control over memory management and are more suitable for modern multi-threaded environments.

## Building the Library

### On Unix-like Systems

To compile and create a shared library (`.so`), run:

```bash
gcc -shared -o libmalloc.so malloc.c
```

- `-shared`: Tells the compiler to create a shared object (dynamic library).
- `-o libmalloc.so`: Specifies the output file name.

### On Windows

To compile and create a shared library (.dll), run:

```bash
gcc -shared -o malloc.dll malloc.c -D_SMALLOC_EXPORTS
```
- `-shared`: Tells the compiler to create a shared object (DLL).
- `-D_SMALLOC_EXPORTS`: Define to export the functions.

## Using the Library

### On Unix-like Systems

1. Set the `LD_LIBRARY_PATH` environment variable to include the directory where `libmalloc.so` is located:

```bash
export LD_LIBRARY_PATH=/path/to/directory
```

2. Compile your program that uses the library:

```bash
gcc -o myprogram myprogram.c -L/path/to/directory -lmalloc
```

3. Run your program:

```bash
./myprogram
```

### On Windows

1. Ensure `malloc.dll` is in the same directory as your executable or in a directory included in the system `PATH`.

2. Compile your program that uses the library:

```bash
gcc -o myprogram myprogram.c -L/path/to/directory -lmallo
```

3. Run your program:

```bash
myprogram.exe
```

## Example Usage

Here is a simple example program (`test.c`) that uses the malloc library:

```c
#include <stdio.h>
#include "malloc.h"

int main() {
    void *ptr = malloc(100);
    if (ptr == NULL) {
        printf("malloc failed\n");
        return 1;
    }
    printf("Allocated 100 bytes at %p\n", ptr);

    free(ptr);
    printf("Memory freed successfully.\n");

    return 0;
}
```

1. Compile the example with:

```bash
gcc -o test test.c -L. -lmalloc
```

2. Run the example:

```bash
myprogram.exe
```
