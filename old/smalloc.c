#include <unistd.h>
#include <string.h>
#include <pthread.h>
// for debugging (printf)
#include <stdio.h>

#include "smalloc.h"

// Define the size of the memory pool
header_t *head, *tail;
// basic mutex for thread safety
pthread_mutex_t global_malloc_lock;

/*
 * This function is used to get the free block of memory that can accomodate the given size.
 * It traverses the linked list and see if there already exist a block of memory that is marked as free
 * and can accomodate the given size.
 * If it finds such a block, it returns the pointer to that block
 */
header_t *get_free_block(size_t size)
{
    header_t *curr = head;
    while (curr) {
        if (curr->s.is_free && curr->s.size >= size) return curr;
        curr = curr->s.next;
    }
    return NULL;
}

/*
 * This function is used to allocate memory of the given size.
 * It first checks if there is a free block that can accomodate the given size.
 * If it finds such a block, it marks the block as in use and returns the pointer to the block.
 * If it doesn't find such a block, it requests more memory from the OS and returns the pointer to the new block.
 * The new block is added to the linked list of blocks.
 */
void *malloc(size_t size)
{
    size_t total_size;
    void *block;
    header_t *header;

    if (!size) return NULL;

    // Lock the mutex
    pthread_mutex_lock(&global_malloc_lock);

    // Find a free block
    header = get_free_block(size);
    if (header) {
        // Mark block as in use
        header->s.is_free = 0;
        pthread_mutex_unlock(&global_malloc_lock);
        // Return the memory block after the header
        return (void*)(header + 1);
    }

    // If we don't have enough space in the existing block, we need to request more memory from the OS
    total_size = sizeof(header_t) + size;
    // sbrk() is used to increase the program's data space
    block = sbrk(total_size);
    if (block == (void*) -1) {
        pthread_mutex_unlock(&global_malloc_lock);
        return NULL;    
    }

    header = block;
    header->s.size = size;
    header->s.is_free = 0;
    header->s.next = NULL;
    if (!head) head = header;
    if (tail) tail->s.next = header;

    tail = header;
    pthread_mutex_unlock(&global_malloc_lock);
    return (void*)(header + 1);
}

void free(void *block)
{
    header_t *header, *tmp;
    void *programbreak;

    if (!block) return;

    pthread_mutex_lock(&global_malloc_lock);

    // Get the header of the block
    // The header is placed before the block
    header = (header_t*)block - 1;
    programbreak = sbrk(0);
    // Check if the block is the last one in the linked list
    // If it is, we can release the memory by moving the program break
    if ((char*)block + header->s.size == programbreak) {
        if (head == tail) {
            head = tail = NULL;
        } else {
            tmp = head;
            while (tmp) {
                if (tmp->s.next == tail) {
                    tmp->s.next = NULL;
                    tail = tmp;
                }
                tmp = tmp->s.next;
            }
        }
        sbrk(0 - sizeof(header_t) - header->s.size);
        pthread_mutex_unlock(&global_malloc_lock);
        return;
    }
    header->s.is_free = 1;
    pthread_mutex_unlock(&global_malloc_lock);
}

/*
 * This function is used to allocate memory for an array of num elements of nsize bytes each.
 * The memory is all set to zero.
 */
void *calloc(size_t num, size_t nsize)
{
    size_t size;
    void *block;

    if (!num || !nsize) return NULL;

    size = num * nsize;
    // Check for overflow
    if (nsize != size / num) return NULL;

    block = malloc(size);
    if (!block) return NULL;

    // Set the memory to zero
    memset(block, 0, size);
    return block;
}

/*
 * This function is used to reallocate memory. It changes the size of the memory block pointed to by block to size bytes.
 * The function may move the memory block to a new location.
 */
void *realloc(void *block, size_t size)
{
    header_t *header;
    void *ret;

    if (!block || !size) return malloc(size);

    header = (header_t*)block - 1;
    if (header->s.size >= size) return block;

    ret = malloc(size);
    if (ret) {
        // Copy the contents of the old block to the new block
        memcpy(ret, block, header->s.size);
        free(block);
    }
    return ret;
}

/*
 * This function is used to print the linked list of memory blocks.
 * It is used for debugging purposes.
 */
void print_mem_list()
{
	header_t *curr = head;
	printf("head = %p, tail = %p \n", (void*)head, (void*)tail);
	while(curr) {
		printf("addr = %p, size = %zu, is_free=%u, next=%p\n",
			(void*)curr, curr->s.size, curr->s.is_free, (void*)curr->s.next);
		curr = curr->s.next;
	}
}
