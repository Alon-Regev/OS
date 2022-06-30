#include "memory.h"

void* memcpy(void* dest, const void* src, int n)
{
    for (int i = 0; i < n; i++)
    {
        ((char*)dest)[i] = ((char*)src)[i];
    }
}

void* memset(void* str, int c, int n)
{
    for (int i = 0; i < n; i++)
    {
        ((unsigned char *)str)[i] = c;
    }
    return str;
}