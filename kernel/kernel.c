#include "../drivers/screen.h"
#include "../helpers/string.h"

void main()
{
    clear_screen();
    set_cursor(0, 0);

    printf("number: %d, float: %.2f, string: %s and more...", 123, 4.56, "hello");
}