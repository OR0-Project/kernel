#include <dev/console.h>
#include <io/port.h>


volatile uint16_t* video_memory = (uint16_t*)CON_VIDEO_MEMORY;
uint16_t color = CON_DEFAULT_COLOR;
uint8_t cx = 0;
uint8_t cy = 0;

// Updates the cursor
void con_update_cursor(int x, int y)
{
	uint16_t pos = y * CONSOLE_W + x;
 
	port_out(0x3D4, 0x0F);
	port_out(0x3D5, (uint8_t) (pos & 0xFF));
	port_out(0x3D4, 0x0E);
	port_out(0x3D5, (uint8_t) ((pos >> 8) & 0xFF));
}

// Advances the cursor position
void _advance_pos(int count) {
    cx++;

    if(cx > CONSOLE_W) {
        cx = 0;
        cy ++;

        if(cy >= CONSOLE_H) {
            cy = CONSOLE_H - 1; // Clamp to last line
        }
    }
}

// Sets the console color
void con_setcolor(uint8_t fore, uint8_t back) {
    color = (back << 4) | (fore & 0x0F);
}

// Clears the console
void con_clear() {
    con_setpos(0, 0);
}

// Writes a string to the console
void con_writes(const char * str) {
    while(*str) {
        con_writec(*str);
        str++;
    }
}

// Handles downscrolling of the console
void handle_scroll() {
    // Shift buffer by one horizontal line
    for(int i = 0; i < CONSOLE_H * CONSOLE_W; i++) {
        video_memory[i] = video_memory[i + CONSOLE_W];
    }
}

// Writes a character to the console.
void con_writec(char c) {
    // Handle newline
    if(c == '\n') {
        cx = 0;
        cy ++;

        if(cy >= CONSOLE_H) {
            cy = CONSOLE_H - 1;
            handle_scroll();
        }

        return;
    }

    // Check if we need to scroll
    if((cy * CONSOLE_W + cx) >= (CONSOLE_W * CONSOLE_H)) {
        handle_scroll();
        return;
    }

    video_memory[cy * CONSOLE_W + cx] = (uint16_t)((color << 8) | c);
    _advance_pos(1);
    con_update_cursor(cx, cy);
}

// Sets the console position
void con_setpos(int x, int y) {
    cx = x;
    cy = y;
    con_update_cursor(cx, cy);
}