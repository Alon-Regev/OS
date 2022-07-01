#include "io.h"
#include "../drivers/screen.h"
#include "../drivers/keyboard.h"
#include <stdarg.h>

void printf(char *format, ...)
{
    char str[256] = {0};
    va_list args;
    va_start(args, format);

    vsprintf(str, format, args);
    print_str(str);

    va_end(args);
}

void puts(char *str)
{
    print_str(str);
    putch('\n');
}

void putchar(char c)
{
    putch(c);
}