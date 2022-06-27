#include "../drivers/screen.h"
#include "../helpers/string.h"

void main()
{
    clear_screen();
    set_cursor(0, 0);

    char str[64] = {0};
    sprintf(str, "d %d, x %x, p %p, f %f, c %c, s %s", 123, 0x456, (void*)0x456, 7.89, 'X', "\"hi\"");
    print_str(str);
}