#include "../libc/io.h"
#include "../drivers/keyboard.h"
#include "../drivers/screen.h"
#include "../libc/string.h"
#include "idt.h"
#include "paging.h"
#include "timer.h"
#include "../libc/ordered_array.h"

void main()
{
    init_idt();
    init_timer(50);
    init_keyboard();

    clear_screen();
    set_cursor(0, 0);

    init_paging();

    printf("Hello world!\n\n");
    // check ordered array
    ordered_array_t arr = create_ordered_array(1000, NULL);
    for (uint32_t i = 0; i < arr.max_size; i++)
    {
        uint32_t bad_rand = ((i ^ 0x0112358D) << (i % 4)) + i;
        insert_ordered_array(&arr, (type_t)(bad_rand % 256));
    }

    for (int i = 0; i < arr.size; i++)
    {
        printf("hi: %d\n", lookup_ordered_array(&arr, i));
    }

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