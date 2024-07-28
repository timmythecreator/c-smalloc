#ifndef SMALLOC_H
#define SMALLOC_H

#include <stddef.h>

#ifdef _WIN32
  #ifdef SMALLOC_EXPORTS
    #define SMALLOC_API __declspec(dllexport)
  #else
    #define SMALLOC_API __declspec(dllimport)
  #endif
#else
  #define SMALLOC_API
#endif

SMALLOC_API void *malloc(size_t size);
SMALLOC_API void free(void *block);
SMALLOC_API void *calloc(size_t num, size_t nsize);
SMALLOC_API void *realloc(void *block, size_t size);

#endif