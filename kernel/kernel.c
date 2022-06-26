#include "../drivers/screen.h"
#include "../helpers/string.h"

void main()
{
    clear_screen();
    set_cursor(0, 0);
    char str[16] = {0};
    print_str(ftoa(-0.000001, str, 2));
}