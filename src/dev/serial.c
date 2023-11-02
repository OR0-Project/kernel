#include <dev/serial.h>

int is_transmit_empty(serial_port_t port) {
   return port_in(port + 5) & 0x20;
}

int serial_received(serial_port_t port) {
   return port_in(port + 5) & 1;
}

uint8_t serial_config(serial_port_t port) {
    port_out(port + 1, 0x00);    // Disable all interrupts
    port_out(port + 3, 0x80);    // Enable DLAB (set baud rate divisor)
    port_out(port + 0, 0x03);    // Set divisor to 3 (lo byte) 38400 baud
    port_out(port + 1, 0x00);    //                  (hi byte)
    port_out(port + 3, 0x03);    // 8 bits, no parity, one stop bit
    port_out(port + 2, 0xC7);    // Enable FIFO, clear them, with 14-byte threshold
    port_out(port + 4, 0x0B);    // IRQs enabled, RTS/DSR set
    port_out(port + 4, 0x1E);    // Set in loopback mode, test the serial chip
    port_out(port + 0, 0xAE);    // Test serial chip (send byte 0xAE and check if serial returns same byte)
    
    // Check if serial is faulty (i.e: not same byte as sent)
    if(port_in(port + 0) != 0xAE) {
        return 1;
    }
    
    // If serial is not faulty set it in normal operation mode
    // (not-loopback with IRQs enabled and OUT#1 and OUT#2 bits enabled)
    port_out(port + 4, 0x0F);
    return 0;
}

uint64_t serial_write(serial_port_t port, uint8_t* buffer, uint64_t size) {
    uint64_t i;

    for(i = 0; i < size; i++) {
        while (is_transmit_empty(port) == 0);
        port_out(port, buffer[i]);
    }

    return i;
}

void serial_print(serial_port_t port, char* str) {
    serial_write(port, (uint8_t*)str, strlen(str));
}

uint64_t serial_read(serial_port_t port, uint8_t* buffer, uint64_t size) {
    uint64_t i = 0;

    while(i < size) {
        while (serial_received(port) == 0);
        buffer[i++] = port_in(port);
    }

    return i;
}

uint64_t serial_read_until(serial_port_t port, uint8_t* buffer, uint64_t size, uint8_t delimiter) {
    uint64_t i = 0;

    while(i < size) {
        while (serial_received(port) == 0);
        uint8_t ch = port_in(port);

        if(ch == delimiter) {
            return i;
        }

        buffer[i++] = ch;
    }

    return i;
}