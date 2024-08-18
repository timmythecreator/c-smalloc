#include "arena.h"
#include "malloc.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

typedef struct Arena {
    struct Arena *next;
    size_t capacity;
    size_t size;
    uint8_t *data;
} Arena;

static Arena* get_local_arena() {
    static Arena arena = {
        .capacity = 0,
        .size = 0,
        .data = NULL,
        .next = NULL,
    };
    return &arena;
}

void _arena_init(size_t capacity) {
    Arena *arena = get_local_arena();
    if (arena->data == NULL) {
        arena->data = smalloc(sizeof(uint8_t) * capacity);
        arena->capacity = capacity;
    }
}

void *arena_alloc(size_t size) {
    Arena *arena = get_local_arena();
    Arena *current = arena;
    assert(current->capacity >= size);

    while (!(current->size + size <= current->capacity)) {
        if (current->next == NULL) {
            Arena *next = smalloc(sizeof(Arena));
            next->capacity = arena->capacity;
            next->size = 0;
            next->next = NULL;
            next->data = smalloc(sizeof(uint8_t) * arena->capacity);
            current->next = next;
        }
        current = current->next;
    }

    uint8_t *data = &current->data[current->size];
    current->size += size;
    return data;
}

void *arena_realloc(void *old_ptr, size_t old_size, size_t new_size) {
    if (new_size <= old_size) return old_ptr;

    void *new_ptr = arena_alloc(new_size);
    char *new_ptr_char = new_ptr;
    char *old_ptr_char = old_ptr;

    for (size_t i = 0; i < old_size; ++i) {
        new_ptr_char[i] = old_ptr_char[i];
    }

    return new_ptr;
}

void arena_reset(void) {
    Arena *current = get_local_arena();
    while (current != NULL) {
        current->size = 0;
        current = current->next;
    }
}

void arena_free(void) {
    Arena *arena = get_local_arena();
    sfree(arena->data);
    arena->capacity = 0;
    arena->size = 0;
    Arena *current = arena->next;
    while (current != NULL) {
        Arena *tmp = current->next;
        sfree(current->data);
        sfree(current);
        current = tmp;
    }
    arena->next = NULL;
}
