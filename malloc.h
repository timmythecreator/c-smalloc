#ifndef MALLOC_H
#define MALLOC_H

#include "platform.h"
#include <stddef.h>

#ifdef WINDOWS_SYSTEM
  #ifdef SMALLOC_EXPORTS
    #define SMALLOC_API __declspec(dllexport)
  #else
    #define SMALLOC_API __declspec(dllimport)
  #endif
#else
  #define SMALLOC_API
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

SMALLOC_API void *smalloc(size_t size);
SMALLOC_API void sfree(void *block);
SMALLOC_API void *scalloc(size_t num, size_t nsize);
SMALLOC_API void *srealloc(void *block, size_t size);

#endif // MALLOC_H
