#ifndef __PROCESS_H
#define __PROCESS_H

#include <types.h>


// Process states
#define PROC_STATE_WAITING 0
#define PROC_STATE_READY 1
#define PROC_STATE_RUNNING 2
#define PROC_STATE_TERM 3
#define PROC_STATE_SUSPENDED 4
#define PROC_STAE_ZOMBIE 5

// Process priorities
#define PROC_PRIO_LOW 0
#define PROC_PRIO_MED 1
#define PROC_PRIO_HIGH 2
#define PROC_PRIO_REALT 3

// Structure to store the process context.
typedef struct procctx_t {
    // General purpose registers
    uint32_t eax;
    uint32_t ebx;
    uint32_t ecx;
    uint32_t edx;
    uint32_t esi;
    uint32_t edi;

    // Stack pointer + base ptr
    uint32_t ebp;
    uint32_t esp;

    // Program counter
    uint32_t eip;

    // Status flags
    uint32_t eflags;
} procctx_t;

// Represents a process
typedef struct proc_t {
    // Process id
    uint32_t pid;

    // Parent process ID
    uint32_t parent;

    // Process state (ready, waiting, etc.)
    uint32_t state;

    // Process execution context
    procctx_t * context;

    // Process priority (low, medium, high, realtime)
    uint32_t priority;

    // -- List functions --

    // Next process
    proc_t * next;

    // Previous process
    proc_t * prev;
} proc_t;

#endif