#include "../drivers/screen.h"
#include "../helpers/string.h"

void main()
{
    clear_screen();
    set_cursor(0, 0);

    char str[128] = {0};
    sprintf(str, "%%d %8d|\n%%x %8x|\n%%p %8p|\n%%f %8.1f|\n%%c %8c|\n%%s %.2s|", 123, 0x456, (void*)0x456, 7.89, 'X', "\"hi\"");
    print_str(str);
}