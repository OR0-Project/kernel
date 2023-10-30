#ifndef __KMEM_H
#define __KMEM_H

#include <types.h>


// 4 megabytes reserved kernel space
#define KMEM_NP_BASE 0xC0000000
#define KMEM_NP_MAX 0xC0400000

// Represents a block of memory
typedef struct kmemblock_t {
    size_t size;

    // The next block of memory
    struct kmemblock_t* next;
} kmemblock_t;

// Initializes the kernel memory space.
void kmem_init();

// Allocates a block of kernel memory
void* kmalloc(size_t size);

// Frees a block of kernel memory
void kfree(void * ptr);

#endif