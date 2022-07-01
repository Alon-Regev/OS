#include "io.h"
#include "../drivers/screen.h"
#include "../drivers/keyboard.h"
#include "string.h"
#include "queue.h"
#include <stdarg.h>

char stdinRaw[256] = {0};
char_queue_t stdin = {stdinRaw, 256, 0, 0};

// --- private functions

// funtion returns true if char should be ignored by stdin.
bool_t stdin_ignore(char c)
{
    return (uint8_t)c >= 0x80;
}

void update_stdin()
{
    // updates occure at newline
    char c;
    do
    {
        c = getch();
        // check special chars
        if(c == '\b')
        {
            erase(&stdin);
            printf("\b \b");    // erase from screen
        }
        else if(!stdin_ignore(c))
        {
            putch(c);
            enqueue(&stdin, c);
        }
    } while (c != '\n');
}

// --- public functions

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

void gets(char* buffer)
{
    if(empty(&stdin))
    {
        update_stdin();
    }
    // get all stdin
    int i = 0;
    do
    {
        buffer[i] = dequeue(&stdin);
        i++;
    } while (!empty(&stdin));
    buffer[i] = 0;
}

char getchar()
{
    if(empty(&stdin))
    {
        update_stdin();
    }
    return dequeue(&stdin);
}

void flush()
{
    flush_queue(&stdin);
}