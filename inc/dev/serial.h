#ifndef __SERIAL_H
#define __SERIAL_H

#include <types.h>
#include <io/port.h>
#include <util/string.h>

typedef enum serial_port_t {
    COM1 = 0x3f8,
    COM2 = 0x2f8,
    COM3 = 0x3e8,
    COM4 = 0x2e8
} serial_port_t;

uint8_t serial_config(serial_port_t port);
uint64_t serial_write(serial_port_t port, uint8_t* buffer, uint64_t size);
void serial_print(serial_port_t port, char* str);
uint64_t serial_read(serial_port_t port, uint8_t* buffer, uint64_t size);
uint64_t serial_read_until(serial_port_t port, uint8_t* buffer, uint64_t size, uint8_t delimiter);

#endif