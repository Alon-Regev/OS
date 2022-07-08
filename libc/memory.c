#include "memory.h"

void* memcpy(void* dest, const void* src, int n)
{
    for (int i = 0; i < n; i++)
    {
        ((char*)dest)[i] = ((const char*)src)[i];
    }
    return dest;
}

void* memset(void* str, int c, int n)
{
    for (int i = 0; i < n; i++)
    {
        ((unsigned char *)str)[i] = c;
    }
    return str;
}

void *memmove(void *dest, const void *src, int n)
{
    if(src >= dest)
    {   // copy forwards
        for (int i = 0; i < n; i++)
        {
            ((char *)dest)[i] = ((const char *)src)[i];
        }
    }
    else
    {   // copy backwards
        for (int i = n - 1; i >= 0; i--)
        {
            ((char *)dest)[i] = ((const char *)src)[i];
        }
    }
    return dest;
}