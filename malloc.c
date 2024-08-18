#include "malloc.h"
#include <stdlib.h>
#include <string.h>

#ifdef WINDOWS_SYSTEM
    #include <windows.h>
#elif UNIX_SYSTEM
    #include <sys/mman.h>
    #include <unistd.h>
#endif

static header_t *head = NULL, *tail = NULL;

static header_t *get_free_block(size_t size) {
    header_t *curr = head;
    while (curr) {
        if (curr->s.is_free && curr->s.size >= size) return curr;
        curr = curr->s.next;
    }
    return NULL;
}

void *smalloc(size_t size) {
    size_t total_size;
    void *block;
    header_t *header;

    if (!size) return NULL;

    header = get_free_block(size);
    if (header) {
        header->s.is_free = 0;
        return (void*)(header + 1);
    }

    total_size = sizeof(header_t) + size;

#ifdef WINDOWS_SYSTEM
    block = VirtualAlloc(NULL, total_size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
#elif UNIX_SYSTEM
    block = mmap(NULL, total_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
#endif

    if (block == NULL || block == (void*)-1) {
        return NULL;
    }

    header = (header_t*)block;
    header->s.size = size;
    header->s.is_free = 0;
    header->s.next = NULL;

    if (!head) head = header;
    if (tail) tail->s.next = header;
    tail = header;

    return (void*)(header + 1);
}

void sfree(void *block) {
    header_t *header;

    if (!block) return;

    header = (header_t*)block - 1;

#ifdef WINDOWS_SYSTEM
    if ((char*)block + header->s.size == (char*)tail + sizeof(header_t)) {
        VirtualFree(header, 0, MEM_RELEASE);
    } else {
        header->s.is_free = 1;
    }
#elif UNIX_SYSTEM
    if ((char*)block + header->s.size == (char*)tail + sizeof(header_t)) {
        munmap(header, sizeof(header_t) + header->s.size);
    } else {
        header->s.is_free = 1;
    }
#endif
}

void *scalloc(size_t num, size_t nsize) {
    size_t size;
    void *block;

    if (!num || !nsize) return NULL;

    size = num * nsize;
    if (nsize != size / num) return NULL;

    block = smalloc(size);
    if (!block) return NULL;

    memset(block, 0, size);
    return block;
}

void *srealloc(void *block, size_t size) {
    header_t *header;
    void *ret;

    if (!block) return smalloc(size);

    header = (header_t*)block - 1;
    if (header->s.size >= size) return block;

    ret = malloc(size);
    if (ret) {
        memcpy(ret, block, header->s.size);
        sfree(block);
    }
    return ret;
}
