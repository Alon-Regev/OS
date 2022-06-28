#ifndef STRING_H
#define STRING_H

#define MAX_N __INT32_MAX__
#define NULL 0

#include <stdarg.h>

// appends up to <n> chars from src to string dest. returns dest.
char* strncat(char *dest, const char *src, int n);

// appends string src to string dest. returns dest.
char* strcat(char *dest, const char *src);

// finds first occurance of char c in string. returns it's pointer or NULL if not found.
const char *strchr(const char *str, int c);

// compares up to <n> bytes of two strings. negative if first is bigger, positive if second, zero if equal.
int strncmp(const char *str1, const char *str2, int n);

// compares two strings. negative if first is bigger, positive if second, zero if equal.
int strcmp(const char *str1, const char *str2);

// copies up to <n> chars of src into destination. returns dest.
char *strncpy(char *dest, const char *src, int n);

// copies content of src into destination. returns dest.
char *strcpy(char *dest, const char *src);

// copies n bytes from of src into destination. returns dest.
void *memcpy(void *dest, const void *src, int n);

// calculates the length of the initial segment of str1 which consists entirely of characters not in str2.
int strcspn(const char *str1, const char *str2);

// computes the length of the string str up to but not including the terminating null character.
int strlen(const char *str);

// finds the first character in the string str1 that matches any character specified in str2.
const char *strpbrk(const char *str1, const char *str2);

// searches for the last occurrence of the character c (an unsigned char) in the string pointed to by the argument str.
const char *strrchr(const char *str, int c);

// calculates the length of the initial segment of str1 which consists entirely of characters in str2.
int strspn(const char *str1, const char *str2);

// finds the first occurrence of the entire string needle (not including the terminating null character) which appears in the string haystack.
const char *strstr(const char *haystack, const char *needle);

// converts integer value to string in some base (up to 16).
char *itoa(int value, char *str, int base);

// converts floating point value to string.
char *ftoa(float value, char *str, int afterPoint);

// extract integer value from string (in decimal base).
int atoi(const char *str);

// creates formatted string and writes it in a buffer using a variable list
void vsprintf(char *str, const char *format, va_list args);

// creates formatted string and writes it in a buffer
void sprintf(char *str, const char *format, ...);

#endif
