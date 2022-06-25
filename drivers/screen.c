#include "screen.h"
#include "ports.h"

// color byte macro from text and background colors
#define colorByte(text, background) (uint8_t)background << 4 + (uint8_t)text

// declarations
void set_cursor_offset(uint16_t offset);
uint16_t get_cursor_offset();
uint16_t get_row(uint16_t offset);
uint16_t get_col(uint16_t offset);

// --- global vars
uint8_t currentColor = colorByte(WHITE, BLACK);
uint8_t *VGA = (uint8_t *)VGA_ADDRESS;

// --- public functions

void set_cursor(int col, int row)
{
    set_cursor_offset(2 * row * VGA_WIDTH + col);
}

void move_cursor(int cells)
{
    set_cursor_offset(get_cursor_offset() + cells * 2);
}

void print_char(char c)
{
    VGA[get_cursor_offset()] = c;
    move_cursor(1);
}

void print_str(char *str);
void printf(char *format, ...);
void clear_screen();
void set_color(Color textColor, Color backgroundColor);

// --- private functions

// function sets cursor offset (in bytes)
void set_cursor_offset(uint16_t offset)
{
    offset /= 2;
    // set data with IO ports
    port_byte_out(SCREEN_CONTROL_PORT, CURSOR_HIGH_BYTE);
    port_byte_out(SCREEN_DATA_PORT, (offset >> 8) & 0xFF);
    port_byte_out(SCREEN_CONTROL_PORT, CURSOR_LOW_BYTE);
    port_byte_out(SCREEN_DATA_PORT, offset & 0xFF);
}

// function returns cursor offset (in bytes)
uint16_t get_cursor_offset()
{
    uint16_t offset = 0;
    // get data from IO ports
    port_byte_out(SCREEN_CONTROL_PORT, CURSOR_HIGH_BYTE);
    offset = port_byte_in(SCREEN_DATA_PORT) << 8;
    port_byte_out(SCREEN_CONTROL_PORT, CURSOR_LOW_BYTE);
    offset += port_byte_in(SCREEN_DATA_PORT);
    return offset * 2;
}

// function returns cursor row based on it's offset
uint16_t get_row(uint16_t offset)
{
    return offset / 2 / VGA_WIDTH;
}

// function returns cursor column based on it's offset
uint16_t get_col(uint16_t offset)
{
    return offset / 2 % VGA_WIDTH;
}
