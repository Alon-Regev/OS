#include "../drivers/screen.h"

void main()
{
    clear_screen();
    set_cursor(0, 0);
    int x = 3;
    char c = 'X';
    printf("char: %c, int: %d", x, c);
}