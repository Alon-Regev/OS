#include "keyboard.h"
#include "../kernel/idt.h"
#include "ports.h"
#include "screen.h"

void default_keyboard_handler(char c);
char getch();

// handlers
keyboard_handler_t keydown_handler = &default_keyboard_handler;
keyboard_handler_t keyup_handler = 0;

char keyboardBuffer[KEYBOARD_BUFFER_SIZE] = {0};
uint8_t keyboardBufferStart = 0;
uint8_t keyboardBufferEnd = 0;

// scancode -> ascii
static const char scancodeLookupTable[] =
    ERR_SCANCODE ESC_SCANCODE "1234567890-+\b\t"        // 0X
    "qwertyuiop[]\n" CTRL_SCANCODE "as"                 // 1X
    "dfghjkl;'`" SHIFT_SCANCODE "\\zxcv"                // 2X
    "bnm,./" SHIFT_SCANCODE "*" ALT_SCANCODE " ";       // 3X

void keyboard_callback(interrupt_handler_stack_t info)
{
    // read scancode from input port
    uint8_t scancode = port_byte_in(SCANCODE_PORT);

    // pick handler (keydown / keyup)
    keyboard_handler_t handler = keydown_handler;
    if(scancode >= KEYUP_OFFSET)
    {
        scancode -= KEYUP_OFFSET;
        handler = keyup_handler;
    }

    // check unknown key
    if(scancode >= sizeof(scancodeLookupTable))
    {
        printf("Unkown keyboard scancode: 0x%x\n", scancode);
        return;
    }
    // send to handler
    if(handler != 0)
    {
        handler(scancodeLookupTable[scancode]);
    }
}

void init_keyboard()
{
    register_interrupt_handler(IRQ(KEYBOARD_IRQ), &keyboard_callback);
}

void default_keyboard_handler(char c)
{
    // put into end of buffer
    keyboardBuffer[keyboardBufferEnd++] = c;
    // forget start if out of space
    if(keyboardBufferEnd == keyboardBufferStart)
    {
        keyboardBufferStart++;
    }
}

char kgetch()
{
    if(keyboardBufferStart == keyboardBufferEnd)
    {
        // nothing to read
        return KGETCH_ERROR;
    }
    return keyboardBuffer[keyboardBufferStart++];
}

char getch()
{
    char c = kgetch();
    while(c == KGETCH_ERROR)
    {
        asm volatile("pause");
        c = kgetch();
    }
    return c;
}