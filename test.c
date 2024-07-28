#include <stdio.h>

#include "malloc.h"

int main() {
    // Example of using malloc
    void *ptr1 = malloc(100);
    if (ptr1 == NULL) {
        printf("malloc failed\n");
        return 1;
    }
    printf("malloc: allocated 100 bytes at %p\n", ptr1);

    // Example of using calloc
    void *ptr2 = calloc(10, 10);
    if (ptr2 == NULL) {
        printf("calloc failed\n");
        free(ptr1);
        return 1;
    }
    printf("calloc: allocated 100 bytes at %p\n", ptr2);

    // Example of using realloc
    void *ptr3 = realloc(ptr1, 200);
    if (ptr3 == NULL) {
        printf("realloc failed\n");
        free(ptr2);
        return 1;
    }
    printf("realloc: reallocated to 200 bytes at %p\n", ptr3);

    // Free the memory
    free(ptr2);
    free(ptr3);
    printf("Memory freed successfully.\n");

    return 0;
}