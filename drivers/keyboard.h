#ifndef KEYBOARD_H
#define KEYBOARD_H

#define KEYBOARD_IRQ 1
#define SCANCODE_PORT 0x60
#define KEYBOARD_LOOKUP_TABLE_LENGTH 0x39
#define KEYUP_OFFSET 0x80

#define KEYBOARD_ERROR (char)0x80
#define ESC_KEY (char)0x81
#define CTRL_KEY (char)0x82
#define SHIFT_KEY (char)0x83
#define ALT_KEY (char)0x84

#define UP_KEY (char)0x85
#define LEFT_KEY (char)0x86
#define RIGHT_KEY (char)0x87
#define DOWN_KEY (char)0x88

#define KGETCH_ERROR 0

#define KEYBOARD_BUFFER_SIZE 256

typedef void (*keyboard_handler_t)(char);

// function initializes irq and callback for keyboard.
// input: none
// return: none
void init_keyboard();

// function checks whether a key press happened or not (char available in keyboard buffer).
// input: none
// return: char or error
char kbhit();

// function returns last pressed key. waits for input if needed.
// input: none
// return: char
char getch();

#endif