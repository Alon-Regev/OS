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
    ordered_array_t arr = create_ordered_array(20, sizeof(uint32_t), NULL);
    uint32_t x = 4;
    insert_ordered_array(&arr, &x);
    x = 7;
    insert_ordered_array(&arr, &x);
    x = 2;
    insert_ordered_array(&arr, &x);
    x = 8;
    insert_ordered_array(&arr, &x);
    x = 0;
    insert_ordered_array(&arr, &x);
    x = 6;
    insert_ordered_array(&arr, &x);
    x = 1500;
    insert_ordered_array(&arr, &x);
    x = 1400;
    insert_ordered_array(&arr, &x);


    for (int i = 0; i < arr.size; i++)
    {
        printf("hi: %d\n", *(uint32_t*)lookup_ordered_array(&arr, i));
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