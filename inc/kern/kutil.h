#ifndef __KUTIL_H
#define __KUTIL_H

#include <types.h>


// Gets the program counter
uint32_t get_program_counter();

// Throws a kernel exception
void throw_ex(const char * ident, const char* message);

// Kernel printf function
void kprintf(const char* format, ...);

#endif