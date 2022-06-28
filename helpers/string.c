#include "string.h"

// --- private functions
void reverse_str(char *str)
{
    int len = strlen(str);
    for (int i = 0; i < len / 2; i++)
    {
        char temp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = temp;
    }
}

// --- public functions

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

const char *strchr(const char *str, int c)
{
    for (const char *p = str; *p != 0; p++)
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
    while (*src != 0 && n-- > 0)
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

void* memcpy(void* dest, const void* src, int n)
{
    for (int i = 0; i < n; i++)
    {
        ((char*)dest)[i] = ((char*)src)[i];
    }
}

int strcspn(const char *str1, const char *str2)
{
    int i = 0;
    for (; str1[i] != 0; i++)
    {
        if (strchr(str2, str1[i]))
        { // str1 char in str2, ended
            return i;
        }
    }
    return i;
}

int strlen(const char *str)
{
    int len = 0;
    while (*str != 0)
    {
        len++;
        str++;
    }
    return len;
}

const char *strpbrk(const char *str1, const char *str2)
{
    for (const char *p = str1; *p != 0; p++)
    {
        if (strchr(str2, *p))
        { // p is first char which appears in str2
            return p;
        }
    }
    // not found
    return NULL;
}

const char *strrchr(const char *str, int c)
{
    const char *ret = NULL;
    for (const char *p = str; *p != 0; p++)
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
        if (!strchr(str2, str1[i]))
        { // str1 char not in str2, ended
            return i;
        }
    }
    return i;
}

const char *strstr(const char *haystack, const char *needle)
{
    while (*haystack != 0)
    {
        if (strcmp(haystack, needle) == 0)
        {
            return haystack;
        }
    }
    return NULL;
}

char *itoa(int value, char *str, int base)
{
    if (value == 0)
    {
        str[0] = '0';
        str[1] = 0;
        return str;
    }

    int isNegative = 0;
    if (base == 10 && value < 0)
    {
        value = -value;
        isNegative = 1;
    }

    const char *digits = "0123456789ABCDEF";
    int i = 0;
    while (value != 0)
    {
        str[i++] = digits[value % base];
        value /= base;
    }
    if (isNegative)
        str[i++] = '-';
    str[i] = 0;

    reverse_str(str);

    return str;
}

char *ftoa(float value, char *str, int afterPoint)
{
    int isNegative = value < 0;
    if (isNegative)
        value = -value;

    int integerPart = (int)value;
    value -= integerPart;
    for (int i = 0; i < afterPoint; i++)
        value *= 10;
    int decimalPart = (int)value;
    // integer part to string
    char *p = str;
    if (isNegative)
        *(p++) = '-';

    itoa(integerPart, p, 10);
    p += strlen(p);

    *(p++) = '.';

    itoa(decimalPart, p, 10);
    int len = strlen(p);
    p += len;

    // add trailing zeros
    for (int i = afterPoint - len; i > 0; i--)
        *(p++) = '0';
    *p = 0;

    return str;
}

int atoi(const char *str)
{
    int res = 0;
 
    for (int i = 0; '0' <= str[i] && str[i] <= '9'; i++)
    {
        res *= 10;
        res += str[i] - '0';
    }

    return res;
}

void vsprintf(char *str, const char *format, va_list args)
{
    for (const char *p = format; *p != 0; p++)
    {
        if (*p == '%')
        {
            p++;
            // get width and precision (%w.p?)
            int width = -1, precision = -1;
            for (int i = 0; i < 2; i++)
            {
                if (*p == '.')
                {
                    p++;
                    precision = atoi(p);
                }
                else if(i == 0)
                {
                    width = atoi(p);
                }
                while ('0' <= *p && *p <= '9')
                    p++;
            }

            // check type
            switch (*p)
            {
            case 'd':
                itoa(va_arg(args, int), str, 10);
                break;
            case 'p':
                str[0] = '0';
                str[1] = 'x';
                itoa(va_arg(args, int), str + 2, 16);
                break;
            case 'x':
                itoa(va_arg(args, int), str, 16);
                break;
            case 'f':
                if(precision == -1)
                    precision = 2;
                ftoa(va_arg(args, double), str, precision);
                break;
            case 's':
                if(precision == -1)
                    precision = MAX_N;
                strncpy(str, va_arg(args, const char *), precision);
                break;
            case 'c':
                str[0] = va_arg(args, int);
                str[1] = 0;
                break;
            case '%':
                str[0] = '%';
                str[1] = 0;
            default:
                break;
            }
            // handle width
            int len = strlen(str);
            str += len;
            for (int i = 0; i < width - len; i++)
            {
                *str = ' ';
                str++;
            }
            *str = 0;
        }
        else
        {
            *str = *p;
            str++;
        }
    }
}

void sprintf(char *str, const char *format, ...)
{
    va_list args;
    va_start(args, format);

    vsprintf(str, format, args);

    va_end(args);
}
