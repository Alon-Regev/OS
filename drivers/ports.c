#include "ports.h"

uint8_t port_byte_in(uint16_t port)
{
    uint8_t result;
    __asm__("in %%dx, %%al"
            : "=a"(result)  // out
            : "d"(port));   // in
    return result;
}

uint16_t port_word_in(uint16_t port)
{
    uint16_t result;
    __asm__("in %%dx, %%ax"
            : "=a"(result)  // out
            : "d"(port));   // int
    return result;
}

void port_byte_out(uint16_t port, uint8_t data)
{
    __asm__("out %%al, %%dx"
            :                           // out
            : "d"(port), "a"(data));    // in
}

void port_word_out(uint16_t port, uint16_t data)
{
    __asm__("out %%ax, %%dx"
            :                           // out
            : "d"(port), "a"(data));    // in
}