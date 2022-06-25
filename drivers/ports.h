#ifndef PORTS_H
#define PORTS_H

#include <stdint.h>

// returns byte from specified port
// input: port address
// return: byte read
uint8_t port_byte_in(uint16_t port);

// returns word from specified port
// input: port address
// return: word read
uint16_t port_word_in(uint16_t port);

// sends byte to specified port
// input: port address, byte to send
// return: none
void port_byte_out(uint16_t port, uint8_t data);

// sends word to specified port
// input: port address, word to send
// return: none
void port_word_out(uint16_t port, uint16_t data);

#endif