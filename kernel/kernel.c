#include "../libc/io.h"
#include "../drivers/keyboard.h"
#include "../drivers/screen.h"
#include "../libc/string.h"
#include "idt.h"
#include "timer.h"

void main()
{
    init_idt();
    init_timer(50);
    init_keyboard();

    clear_screen();
    set_cursor(0, 0);

    printf("Hello world!\n\n");

    while(1)
    {
        printf("Enter your name: ");
        char name[16];
        gets(name);
        name[strcspn(name, "\n")] = 0;
        printf("Enter favorite char: ");
        char favorite = getchar();

        printf("Your name is \"%s\" and you like '%c'!\n\n", name, favorite);
        flush();
    }
}