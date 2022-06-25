#ifndef SCREEN_H
#define SCREEN_H

#define VGA_ADDRESS 0xB8000

#define VGA_WIDTH 80
#define VGA_HEIGHT 25

#define TAB_SIZE 4
#define TAB_OFFSET 2 * TAB_SIZE

#define SCREEN_CONTROL_PORT 0x3D4
#define SCREEN_DATA_PORT 0x3D5
#define CURSOR_HIGH_BYTE 14
#define CURSOR_LOW_BYTE 15

// enum for selecting print colors (either text or background).
// 4 bit range (16 options)
typedef enum Color
{
    BLACK = 0,
    BLUE,
    GREEN,
    CYAN,
    RED,
    PURPLE,
    BROWN,
    LIGHT_GRAY,
    GRAY,
    LIGHT_BLUE,
    LIGHT_GREEN,
    LIGHT_CYAN,
    LIGHT_RED,
    PINK,
    YELLOW,
    WHITE
} Color;

// function sets cursor position on the screen.
// input: column and row on screen
// return: none
void set_cursor(int col, int row);

// function moves cursor by <n> cells.
// input: number of cells to move
// return: none
void move_cursor(int cells);

// function prints string on screen at cursor position.
// input: string to print
// return: none
void print_str(char *str);

// function prints a char on screen at cursor position.
// input: char to print
// return: none
void print_char(char c);

// function prints a formatted string on screen.
// input: format and arguments to print
// return: none
void printf(char *format, ...);

// function clears all text and colors from screen.
// input: none
// return: none
void clear_screen();

// function sets color for future prints.
// input: text and background colors to use
// return: none
void set_color(Color textColor, Color backgroundColor);

#endif