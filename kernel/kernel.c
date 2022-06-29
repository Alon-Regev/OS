#include "../drivers/screen.h"
#include "../helpers/string.h"

void main()
{
    clear_screen();
    set_cursor(0, 0);

    printf("Hello world!\n");
}