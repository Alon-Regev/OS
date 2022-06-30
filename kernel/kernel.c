#include "../drivers/screen.h"
#include "../helpers/string.h"
#include "idt.h"

void main()
{
    init_idt();

    clear_screen();
    set_cursor(0, 0);

    printf("Hello world!\n");
    
    // test interrupts
    asm volatile("int $0x03");
}