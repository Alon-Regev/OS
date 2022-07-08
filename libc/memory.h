#ifndef MEMORY_H
#define MEMORY_H

// copies n bytes from of src into destination. returns dest.
void *memcpy(void *dest, const void *src, int n);

// copies n bytes from of src into destination. can overlap. returns dest.
void *memmove(void *dest, const void *src, int n);

// initialized first <n> bytes of str with char <c>.
void *memset(void *str, int c, int n);

#endif