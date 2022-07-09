#include "../libc/io.h"
#include "../drivers/keyboard.h"
#include "../drivers/screen.h"
#include "../libc/string.h"
#include "idt.h"
#include "paging.h"
#include "timer.h"

void main()
{
    init_idt();
    init_timer(50);
    init_keyboard();

    clear_screen();
    set_cursor(0, 0);

    init_paging();

    printf("Hello world!\n\n");

    while (1)
    {
        int x, y, ret;
        do
        {
            printf("Enter two numbers: ");
            ret = scanf("%d:%d", &x, &y);
            flush();
        } while (ret != 2);
        printf("x + y = %d\n", x + y);
    }

    PANIC("END");
}