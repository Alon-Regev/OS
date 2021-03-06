#ifndef IO_H
#define IO_H

// function prints a formatted string on screen.
// input: format and arguments to print
// return: number of chars printed
int printf(char *format, ...);

// function extracts data from input.
// input: format and pointers to put data in
// return: number of args filled
int scanf(char *format, ...);

// function prints string with newline char.
// input: string to print
// return: none
void puts(char *str);

// function prints one char.
// input: char to print
// return: none
void putchar(char c);

// function reads string until newline.
// input: buffer to store string in.
// return: none
void gets(char* buffer);

// function receives one char after newline.
// input: none
// return: read char
char getchar();

// function clears stdin.
// input: none
// return: none
void flush();

#endif