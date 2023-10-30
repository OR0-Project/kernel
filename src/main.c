#include <kern/kernel.h>
#include <kern/kutil.h>
#include <kern/kmem.h>
#include <dev/console.h>
#include <util/string.h>
#include <types.h>
#include <build.h>

// For testing
#include <arch/cpu.h>

#define OS_BANNER "                 .___\n\
  ____  ______ __| _/\n\
 /  _ \\/  ___// __ | \n\
(  <_> )___ \\/ /_/ | \n\
 \\____/____  >____ | \n\
           \\/     \\/\n\n"

// Shows the kernel startup banner
void splash() {
	con_setcolor(0xF, 0);
	con_clear();
    // Show kernel brand and system info
    con_setpos(0, 0);
    con_setcolor(0xA, 0);
    con_writes(":: OS Kernel v1.0. Copyright (C) 2023.\n");
    con_writes(":: Commit: ");
    con_writes(B_GIT_HASH);
    con_writes(", Compiled: ");
    con_writes(B_COMPTIME_START);
    con_writes("\n\n");
    con_setcolor(0xF, 0);

    con_writes(OS_BANNER);

    // Get CPU info
    cpu_info_t * cpu = get_cpu_info();
    con_setcolor(0xE, 0);
    con_writes("Processor: ");
    con_setcolor(0xF, 0);
    con_writes(cpu->brand);
    con_writec('\n');
}

// Sets up non paged kernel memory space
void init_kernel_mem() {
    // Init
    kmem_init();

    // Do self test to ensure allocator is working correctly
    void* ptr = kmalloc(32);

    if(ptr)	{ con_writes("Kmem self test succeeded!\n"); }
    else	{ throw_ex("kmain", "Failed to setup kernel memory space."); }

    kfree(ptr);
}

/**
 * Kernel entry point.
 * */
void kernel_main() {
    init_kernel_mem();	// TODO: refactor (after printf)
	splash();				// TODO: refactor (after printf)

	read_tsc();

    // test
    volatile char* mt = (char*)0x2a5C0;

    *mt = 'a';
    mt++;
    *mt = 'b';
    mt++;
    *mt = 'c';
    mt++;
    while(1);

    throw_ex("kmain", "End of kernel - development needed");

	return;
}
