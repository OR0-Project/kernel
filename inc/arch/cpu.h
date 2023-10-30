#ifndef __CPUID_H
#define __CPUID_H

#include <types.h>


typedef struct cpu_info_t {
    uint32_t cores;
    uint32_t threads;
    char brand[49];
    uint32_t family;
    uint32_t model;
    uint32_t stepping;
} cpu_info_t;


extern void cpuid(uint32_t code, uint32_t* eax, uint32_t* ebx, uint32_t* ecx, uint32_t* edx);

// Gets the CPU brand string
void get_cpu_brand_string(char* brand_string);

// Gets information about the CPU
cpu_info_t * get_cpu_info();

uint64_t read_msr(uint32_t msr_id);
void write_msr(uint32_t msr_id, uint64_t msr_value);

uint64_t read_tsc();

#endif