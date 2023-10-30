#ifndef _STRING_H
#define _STRING_H

#include <types.h>


// Gets the string length
uint32_t strlen(const char *str);

// Converts an integer to ascii
char * itoa(int value, char * str, int base);

// Checks if a string is whitespace only
bool strisws(const char* str);

#endif