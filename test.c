#include <stdio.h>

#include "malloc.h"
#include "arena.h"

int main() {
    ////////////////////////////////////////////////////////////////////////////
    // Example of using malloc
    void *ptr1_malloc = smalloc(100);
    if (ptr1_malloc == NULL) {
        printf("malloc failed\n");
        return 1;
    }
    printf("malloc: allocated 100 bytes at %p\n", ptr1_malloc);

    // Example of using calloc
    void *ptr2_malloc = scalloc(10, 10);
    if (ptr2_malloc == NULL) {
        printf("calloc failed\n");
        sfree(ptr1_malloc);
        return 1;
    }
    printf("calloc: allocated 100 bytes at %p\n", ptr2_malloc);

    // Example of using realloc
    void *ptr3_malloc = srealloc(ptr1_malloc, 200);
    if (ptr3_malloc == NULL) {
        printf("realloc failed\n");
        sfree(ptr2_malloc);
        return 1;
    }
    printf("realloc: reallocated to 200 bytes at %p\n", ptr3_malloc);

    // Free the memory
    sfree(ptr2_malloc);
    sfree(ptr3_malloc);
    printf("Memory freed successfully.\n");

    ////////////////////////////////////////////////////////////////////////////
    // Example of using arena
    // arena initialization
    arena_init(1024);
    printf("Arena initialized with 1024 bytes.\n");

    // Example of using arena_alloc to allocate a small block
    void *ptr1_arena = arena_alloc(100);
    if (ptr1_arena == NULL) {
        printf("arena_alloc failed\n");
        return 1;
    }
    printf("arena_alloc: allocated 100 bytes at %p\n", ptr1_arena);

    // Example of using arena_alloc to allocate a large block
    void *ptr2_arena = arena_alloc(200);
    if (ptr2_arena == NULL) {
        printf("arena_alloc failed\n");
        arena_free();
        return 1;
    }
    printf("arena_alloc: allocated 200 bytes at %p\n", ptr2_arena);

    // Example of using arena_realloc to reallocate a block
    void *ptr3_arena = arena_realloc(ptr1_arena, 100, 300);
    if (ptr3_arena == NULL) {
        printf("arena_realloc failed\n");
        arena_free();
        return 1;
    }
    printf("arena_realloc: reallocated to 300 bytes at %p\n", ptr3_arena);

    // Free the memory
    arena_free();
    printf("Arena memory freed successfully.\n");

    return 0;
}
