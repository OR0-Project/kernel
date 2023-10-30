#ifndef __TYPES_H
#define __TYPES_H


// integer types
typedef unsigned char uint8_t;
typedef signed char int8_t;
typedef unsigned short uint16_t;
typedef signed short int16_t;
typedef unsigned long uint32_t;
typedef signed long int32_t;
typedef unsigned long long uint64_t;
typedef signed long long int64_t;

// boolean types
typedef uint8_t bool;
#define true 0b1u
#define false 0b0u

// pointer types
typedef uint32_t size_t;
#define NULL ((void*)0)

// integer min and max values
#define UINT8_MAX (0xFF)
#define INT8_MAX (0x7F)
#define INT8_MIN (-0x80)
#define UINT16_MAX (0xFFFF)
#define INT16_MAX (0x7FFF)
#define INT16_MIN (-0x8000)
#define UINT32_MAX (0xFFFFFFFF)
#define INT32_MAX (0x7FFFFFFF)
#define INT32_MIN (-0x80000000)
#define UINT64_MAX (0xFFFFFFFFFFFFFFFFULL)
#define INT64_MAX (0x7FFFFFFFFFFFFFFFULL)
#define INT64_MIN (-0x8000000000000000LL)


#endif