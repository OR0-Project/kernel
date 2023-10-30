#include <arch/cpu.h>
#include <kern/kmem.h>
#include <kern/kutil.h>
#include <types.h>
#include <util/string.h>

// Stores the current CPU information state
cpu_info_t * cpu_info_state = NULL;

// Get brand string
void get_cpu_brand_string(char* brand) {
    uint32_t registers[4];
    uint32_t code;

    // Retrieve CPU brand string (concatenating sub-leaves)
    for (code = 0x80000002; code <= 0x80000004; code++) {
        cpuid(code, &registers[0], &registers[1], &registers[2], &registers[3]);
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                *brand++ = (char)(registers[i] >> (j * 8));
            }
        }
    }

    // Null-terminate the brand string
    *brand = '\0';
}

/**
 * Gets information about the CPU.
 * 
 * Retrieved CPU info is persistently kept in kernel memory.
 */
cpu_info_t * get_cpu_info() {
    if(cpu_info_state != NULL)
        return cpu_info_state;

    cpu_info_state = kmalloc(sizeof(cpu_info_t));

    if(cpu_info_state == NULL)
        throw_ex("get_cpu_info", "Unable to allocate memory.");

    // Get brand string
    get_cpu_brand_string(cpu_info_state->brand);

    if(strisws(cpu_info_state->brand)) {
        char genericBrand[] = "Generic x86 Processor";

        for(int i = 0; i <= strlen(genericBrand); i++) {
            cpu_info_state->brand[i] = genericBrand[i];
        }
    }

    // Get family, model, and stepping
    uint32_t eax, ebx, ecx, edx;
    cpuid(1, &eax, &ebx, &ecx, &edx);

    cpu_info_state->family = (eax >> 8) & 0xf;
    cpu_info_state->model = (eax >> 4) & 0xf;
    cpu_info_state->stepping = eax & 0xf;

    return cpu_info_state;
}