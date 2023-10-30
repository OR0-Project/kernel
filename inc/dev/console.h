#ifndef __CONSOLE_H
#define __CONSOLE_H

#include <types.h>


#define CON_VIDEO_MEMORY 0xB8000
#define CON_DEFAULT_COLOR 0x0F
#define CONSOLE_W 80
#define CONSOLE_H 25

// Sets the console color
void con_setcolor(uint8_t fore, uint8_t back);

// Clears the console
void con_clear();

// Writes a string to the console
void con_writes(const char * str);

// Writes a character to the console.
void con_writec(char c);

// Sets the console position
void con_setpos(int x, int y);

// Updates the cursor
void con_update_cursor(int x, int y);

#endif