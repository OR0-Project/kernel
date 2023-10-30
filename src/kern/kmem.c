#include <kern/kmem.h>


// Kernel memory
char kmem[KMEM_NP_MAX - KMEM_NP_BASE];

// The start block
kmemblock_t* start_block = NULL;

// Initializes the kernel memory space.
void kmem_init() {
    start_block = (kmemblock_t*)kmem;
    start_block->size = (KMEM_NP_MAX - KMEM_NP_BASE) - sizeof(kmemblock_t);
    start_block->next = NULL;
}

// Allocates a block of kernel memory
void* kmalloc(size_t size) {
    if(size == 0)
        return NULL; // 0 length kmem block should not be allocated
    
    kmemblock_t* cur = start_block;
    kmemblock_t* prev = NULL;

    while(cur) {
        if (cur->size >= size) {
            // If the block is larger than needed, split it
            if (cur->size > size + sizeof(kmemblock_t)) {
                kmemblock_t* new_block = (kmemblock_t*)((char*)cur + size + sizeof(kmemblock_t));
                new_block->size = cur->size - size - sizeof(kmemblock_t);
                new_block->next = cur->next;
                cur->size = size;
                cur->next = new_block;
            }

            // Mark the block as in use
            if (prev)
                prev->next = cur->next;
            else
                start_block = cur->next;

            return (char*)cur + sizeof(kmemblock_t);
        }

        prev = cur;
        cur = cur->next;
    }

    // No free block
    return NULL;
}

// Frees a block of kernel memory
void kfree(void * ptr) {
    if(ptr == NULL)
        return; // ignore null pointer

    // Mark the block as free and coalesce adjacent free blocks
    kmemblock_t* current = (kmemblock_t*)((char*)ptr - sizeof(kmemblock_t));
    current->size += sizeof(kmemblock_t); // Account for the block's header

    kmemblock_t* temp = start_block;
    kmemblock_t* prev = NULL;

    while (temp) {
        if ((char*)temp > (char*)current)
            break;
        prev = temp;
        temp = temp->next;
    }

    if (prev) {
        prev->next = current;
        if ((char*)prev + prev->size == (char*)current) {
            prev->size += current->size;
            current = prev;
        }
    } else {
        start_block = current;
    }

    if (temp && (char*)current + current->size == (char*)temp) {
        current->size += temp->size;
        current->next = temp->next;
    }
}