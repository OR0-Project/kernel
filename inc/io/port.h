#ifndef PORT_H
#define PORT_H

#include <types.h>


uint8_t port_in(uint16_t port);
void port_out(uint16_t port, uint8_t data);

#endif