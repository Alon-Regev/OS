#include "io.h"
#include "../drivers/screen.h"
#include "../drivers/keyboard.h"
#include "string.h"
#include "queue.h"

char stdinRaw[256] = {0};
char_queue_t stdin = {stdinRaw, 256, 0, 0};

// --- private functions

// funtion returns true if char should be ignored by stdin.
bool_t stdin_ignore(char c)
{
    return (uint8_t)c >= 0x80 || c == '\b';
}

void update_stdin()
{
    char_queue_t *ptr = &stdin;
    // updates occure at newline
    char c;
    do
    {
        c = getch();
        // check special chars
        if(c == '\b' && !empty(&stdin))
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

int printf(char *format, ...)
{
    char str[256] = {0};
    va_list args;
    va_start(args, format);

    int ret = vsprintf(str, format, args);
    print_str(str);

    va_end(args);
    return ret;
}

int scanf(char *format, ...)
{
    char buffer[256] = {0};
    gets(buffer);

    va_list args;
    va_start(args, format);

    int charCount = 0;
    int ret = vsscanf(buffer, format, &charCount, args);
    // restore stdin
    int i = charCount;
    while (buffer[i])
    {
        enqueue(&stdin, buffer[i++]);
    }

    va_end(args);
    return ret;
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