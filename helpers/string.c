#include "string.h"

char *strncat(char *dest, const char *src, int n)
{
    int destLen = strlen(dest), i = 0;
    for (; i < n && src[i] != 0; i++)
    {
        dest[destLen + i] = src[i];
    }
    dest[destLen + i] = 0;
    return dest;
}

char *strcat(char *dest, const char *src)
{
    return strncat(dest, src, MAX_N);
}

char *strchr(const char *str, int c)
{
    for (char *p = str; *p != 0; p++)
    {
        if (*p == c)
            return p;
    }
    return NULL;
}

int strncmp(const char *str1, const char *str2, int n)
{
    while (*str1 != 0 && n-- > 0)
    {
        if (*str1 != *str2) // difference between strings
        {
            break;
        }
        str1++;
        str2++;
    }
    // return ASCII difference between last checked chars
    return *(const unsigned char *)str1 - *(const unsigned char *)str2;
}

int strcmp(const char *str1, const char *str2)
{
    return strncmp(str1, str2, MAX_N);
}

char *strncpy(char *dest, const char *src, int n)
{
    char *p = dest;
    while (src != 0 && n-- > 0)
    {
        *p = *src;
        p++;
        src++;
    }
    *p = 0;
    return dest;
}

char *strcpy(char *dest, const char *src)
{
    return strncpy(dest, src, MAX_N);
}

int strcspn(const char *str1, const char *str2)
{
    int i = 0;
    for (; str1[i] != 0; i++)
    {
        if(strchr(str2, str1[i]))
        {   // str1 char in str2, ended
            return i;
        }
    }
    return i;
}

int strlen(const char *str)
{
    int len = 0;
    while(*str != 0)
    {
        len++;
    }
    return len;
}

char *strpbrk(const char *str1, const char *str2)
{
    for (char *p = str1; *p != 0; p++)
    {
        if(strchr(str2, *p))
        {   // p is first char which appears in str2
            return p;
        }
    }
    // not found
    return NULL; 
}

char *strrchr(const char *str, int c)
{
    char *ret = NULL;
    for (char *p = str; *p != 0; p++)
    {
        if (*p == c)
            ret = p;
    }
    return ret;
}

int strspn(const char *str1, const char *str2)
{
    int i = 0;
    for (; str1[i] != 0; i++)
    {
        if(!strchr(str2, str1[i]))
        {   // str1 char not in str2, ended
            return i;
        }
    }
    return i;
}

char *strstr(const char *haystack, const char *needle)
{
    while(*haystack != 0)
    {
        if(strcmp(haystack, needle) == 0)
        {
            return haystack;
        }
    }
    return NULL;
}
