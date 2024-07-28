#ifndef MEMALLOC_H
#define MEMALLOC_H

#include <unistd.h>

typedef char ALIGN[16]; // 16 bytes alignment

union header {
    struct {
        size_t size;
        unsigned is_free;
        union header *next;
    } s;
    ALIGN stub; // Align the header to 16 bytes
};
typedef union header header_t;

// Function prototypes
void free(void *block);
void *malloc(size_t size);
void *calloc(size_t num, size_t nsize);
void *realloc(void *block, size_t size);

// Additional functions for debugging
void print_mem_list();

#endif