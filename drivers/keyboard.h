#ifndef KEYBOARD_H
#define KEYBOARD_H

#define KEYBOARD_IRQ 1
#define SCANCODE_PORT 0x60
#define KEYBOARD_LOOKUP_TABLE_LENGTH 0x39
#define KEYUP_OFFSET 0x80

#define ERR_SCANCODE "\x80"
#define ESC_SCANCODE "\x81"
#define CTRL_SCANCODE "\x82"
#define SHIFT_SCANCODE "\x83"
#define ALT_SCANCODE "\x84"

#define KGETCH_ERROR 0

#define KEYBOARD_BUFFER_SIZE 256

typedef void (*keyboard_handler_t)(char);

// function initializes irq and callback for keyboard.
// input: none
// return: none
void init_keyboard();

// function returns last pressed key, or error if no available key.
// input: none
// return: char or error
char kgetch();

// function returns last pressed key. waits for input if needed.
// input: none
// return: char
char getch();

#endif