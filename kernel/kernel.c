#include "../drivers/screen.h"
#include "../helpers/string.h"

void main()
{
    clear_screen();
    set_cursor(0, 0);

    for (int i = 0; i < 100; i++)
    {
        printf("Hello World %d\n", i);
        for (int t = 0; t < 1e6; t++)
            ;
    }
}