#ifndef MALLOC_H
#define MALLOC_H

#include <stddef.h>

#ifdef _WIN32
  #ifdef SMALLOC_EXPORTS
    #define MALLOC_API __declspec(dllexport)
  #else
    #define MALLOC_API __declspec(dllimport)
  #endif
#else
  #define MALLOC_API
#endif

typedef char ALIGN[16];

union header {
    struct {
        size_t size;
        unsigned is_free;
        union header *next;
    } s;
    ALIGN stub;
};
typedef union header header_t;

MALLOC_API void *malloc(size_t size);
MALLOC_API void free(void *block);
MALLOC_API void *calloc(size_t num, size_t nsize);
MALLOC_API void *realloc(void *block, size_t size);

#endif
