#ifndef ARENA_H
#define ARENA_H

#include "platform.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef WINDOWS_SYSTEM
  #ifdef ARENA_EXPORTS
    #define ARENA_API __declspec(dllexport)
  #else
    #define ARENA_API __declspec(dllimport)
  #endif
#else
  #define ARENA_API
#endif

ARENA_API void _arena_init(size_t capacity);
ARENA_API void *arena_alloc(size_t size);
ARENA_API void arena_reset(void);
ARENA_API void arena_free(void);
ARENA_API void *arena_realloc(void *old_ptr, size_t old_size, size_t new_size);

#define arena_init(size) \
    {_arena_init(size); atexit(arena_free); }

#endif // ARENA_H
