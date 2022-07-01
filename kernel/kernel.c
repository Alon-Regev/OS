#include "../libc/io.h"
#include "../drivers/keyboard.h"
#include "../drivers/screen.h"
#include "idt.h"
#include "timer.h"

void main()
{
    init_idt();
    init_timer(50);
    init_keyboard();

    clear_screen();
    set_cursor(0, 0);

    printf("Hello world!\n");

    while(1)
    {
        putchar(getch());
    }
}