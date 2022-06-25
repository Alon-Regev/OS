#include "../drivers/screen.h"

void main()
{
    set_cursor(2, 0);
    print_char('X');
    move_cursor(1);
    print_char('Y');
    move_cursor(2);
    print_char('Z');
}