#include "../drivers/screen.h"

void main()
{
    clear_screen();
    set_cursor(0, 0);
    print_str("Hello\tworld!");
}