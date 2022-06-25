#include "screen.h"
#include "ports.h"

// color byte macro from text and background colors
#define colorByte(text, background) (uint8_t)background << 4 + (uint8_t)text

// --- global vars
uint8_t currentColor = colorByte(WHITE, BLACK);

// --- public functions

void set_cursor(int col, int row)
{
    uint16_t pos = row * VGA_WIDTH + col;

    // set data with IO ports
    port_byte_out(SCREEN_CONTROL_PORT, CURSOR_HIGH_BYTE);
    port_byte_out(SCREEN_DATA_PORT, (pos >> 8) & 0xFF);
    port_byte_out(SCREEN_CONTROL_PORT, CURSOR_LOW_BYTE);
    port_byte_out(SCREEN_DATA_PORT, pos & 0xFF);
}

void print_str(char *str);
void print_char(char c);
void printf(char *format, ...);
void clear_screen();
void set_color(Color textColor, Color backgroundColor);
