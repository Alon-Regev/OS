#include "keyboard.h"
#include "../kernel/idt.h"
#include "ports.h"
#include "screen.h"
#include "../libc/types.h"

#define ERR_SCANCODE "\x80"
#define ERSC ERR_SCANCODE
#define ESC_SCANCODE "\x81"
#define CTRL_SCANCODE "\x82"
#define SHIFT_SCANCODE "\x83"
#define ALT_SCANCODE "\x84"

#define ARROW_UP "\x85"    // scancode 0x48
#define ARROW_LEFT "\x86"  // scancode 0x4B
#define ARROW_RIGHT "\x87" // scancode 0x4D
#define ARROW_DOWN "\x88"  // scancode 0x50

void default_keyboard_handler(char c);

// handlers
keyboard_handler_t keydown_handler = &default_keyboard_handler;
keyboard_handler_t keyup_handler = 0;

char keyboardBuffer[KEYBOARD_BUFFER_SIZE] = {0};
uint8_t keyboardBufferStart = 0;
uint8_t keyboardBufferEnd = 0;

// scancode -> ascii
static const char scancodeLookupTable[] =
    ERR_SCANCODE ESC_SCANCODE "1234567890-+\b\t"                                                            // 0X
                              "qwertyuiop[]\n" CTRL_SCANCODE "as"                                           // 1X
                              "dfghjkl;'`" SHIFT_SCANCODE "\\zxcv"                                          // 2X
                              "bnm,./" SHIFT_SCANCODE "*" ALT_SCANCODE " " ERSC ERSC ERSC ERSC ERSC ERSC "" // 3X
    ERSC ERSC ERSC ERSC ERSC ERSC ERSC ERSC ARROW_UP ERSC ERSC ARROW_LEFT ERSC ARROW_RIGHT ERSC ERSC        // 4X
        ARROW_DOWN;                                                                                         // 5X
static const char shiftScancodeLookupTable[] =
    ERR_SCANCODE ESC_SCANCODE "!@#$%^&*()_+\b\t"                                                            // 0X
                              "QWERTYUIOP{}\n" CTRL_SCANCODE "AS"                                           // 1X
                              "DFGHJKL:\"~" SHIFT_SCANCODE "|ZXCV"                                          // 2X
                              "BNM<>?" SHIFT_SCANCODE "*" ALT_SCANCODE " " ERSC ERSC ERSC ERSC ERSC ERSC "" // 3X
    ERSC ERSC ERSC ERSC ERSC ERSC ERSC ERSC ARROW_UP ERSC ERSC ARROW_LEFT ERSC ARROW_RIGHT ERSC ERSC        // 4X
        ARROW_DOWN;                                                                                         // 5X

// input states
bool_t shift = FALSE;
bool_t ctrl = FALSE;

void keyboard_callback(interrupt_handler_stack_t info)
{
    // read scancode from input port
    uint8_t scancode = port_byte_in(SCANCODE_PORT);

    // pick handler (keydown / keyup)
    bool_t keydown = scancode < KEYUP_OFFSET;
    keyboard_handler_t handler = keydown_handler;
    if (!keydown)
    {
        // keyup
        scancode -= KEYUP_OFFSET;
        handler = keyup_handler;
    }

    // check unknown key
    if (scancode >= sizeof(scancodeLookupTable))
    {
        return;
    }
    // get char
    char c = scancodeLookupTable[scancode];

    if (c == SHIFT_KEY)
        shift = keydown;
    else if (c == CTRL_KEY)
        ctrl = keydown;

    if (c == KEYBOARD_ERROR)
    {
        return;
    }

    if (shift)
    {
        c = shiftScancodeLookupTable[scancode];
    }

    // send to handler
    if (handler != 0)
    {
        handler(c);
    }
}

void init_keyboard()
{
    register_interrupt_handler(IRQ(KEYBOARD_IRQ), &keyboard_callback);
}

void default_keyboard_handler(char c)
{
    if (c == KEYBOARD_ERROR)
        return;
    // put into end of buffer
    keyboardBuffer[keyboardBufferEnd++] = c;
    // forget start if out of space
    if (keyboardBufferEnd == keyboardBufferStart)
    {
        keyboardBufferStart++;
    }
}

char kbhit()
{
    return keyboardBufferStart != keyboardBufferEnd;
}

char getch()
{
    while (!kbhit())
    {
        asm volatile("pause");
    }
    return keyboardBuffer[keyboardBufferStart++];
}