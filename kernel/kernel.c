#include "../drivers/screen.h"
#include "../libc/string.h"
#include "idt.h"
#include "timer.h"

void main()
{
    init_idt();
    init_timer(100);

    clear_screen();
    set_cursor(0, 0);

    printf("Hello world!\n");
}