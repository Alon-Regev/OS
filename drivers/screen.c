#include "screen.h"
#include "ports.h"
#include "../libc/string.h"
#include "../libc/memory.h"

// color byte macro from text and background colors
#define colorByte(text, background) ((uint8_t)background << 4) + (uint8_t)text
#define DEFAULT_COLOR colorByte(WHITE, BLACK)

// declarations
void set_cursor_offset(uint16_t offset);
uint16_t get_cursor_offset();
uint16_t get_row(uint16_t offset);
uint16_t get_col(uint16_t offset);
uint16_t base_char_print(char c, uint16_t offset);

// --- global vars
uint8_t currentColor = DEFAULT_COLOR;
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
    uint16_t offset = get_cursor_offset();
    offset = base_char_print(c, offset);
    set_cursor_offset(offset);
}

void print_str(char *str)
{
    uint16_t offset = get_cursor_offset();
    for (char *c = str; *c != 0; c++)
    {
        offset = base_char_print(*c, offset);
    }
    set_cursor_offset(offset);
}

void clear_screen()
{
    for (int i = 0; i < VGA_WIDTH * VGA_HEIGHT; i++)
    {
        VGA[2 * i] = ' ';
        VGA[2 * i + 1] = DEFAULT_COLOR;
    }
}

void set_color(Color textColor, Color backgroundColor)
{
    currentColor = colorByte(textColor, backgroundColor);
}

void printf(char *format, ...)
{
    char str[256] = {0};
    va_list args;
    va_start(args, format);

    vsprintf(str, format, args);
    print_str(str);

    va_end(args);
}

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

// function for basic char printing without affecting cursor
// input: char to print, offset to print in
// return: new offset after print
uint16_t base_char_print(char c, uint16_t offset)
{
    int newOffset;
    switch (c)
    {
    case '\n':
        newOffset = 2 * (get_row(offset) + 1) * VGA_WIDTH;
        break;
    case '\r':
        newOffset = 2 * get_row(offset) * VGA_WIDTH;
        break;
    case '\t':
        newOffset = offset / TAB_OFFSET * TAB_OFFSET + TAB_OFFSET;
        break;
    case '\b':
        if (get_col(offset) != 0)
            newOffset = offset - 2;
        break;
    default:
        VGA[offset] = c;
        VGA[offset + 1] = currentColor;
        newOffset = offset + 2;
        break;
    }
    // check scroll
    if (newOffset >= VGA_WIDTH * VGA_HEIGHT * 2)
    {
        // copy rows upwards
        int rowLen = VGA_WIDTH * 2; // row size
        for (int i = 1; i < VGA_HEIGHT; i++)
        {
            memcpy(VGA + rowLen * (i - 1), VGA + rowLen * i, rowLen);
        }
        // blank last line
        char *lastLine = VGA + VGA_WIDTH * 2 * (VGA_HEIGHT - 1);
        for (int i = 0; i < VGA_WIDTH; i++)
        {
            lastLine[2 * i] = lastLine[2 * i + 1] = 0;
        }
        newOffset -= rowLen;
    }
    return newOffset;
}
