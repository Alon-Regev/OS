#include "../drivers/ports.h"

void main()
{
    // get cursor position
    // ask from port 0x3D4 for bytes 14 (high) and 15 (low)
    // receive in port 0x3D5
    port_byte_out(0x3D4, 14);
    uint16_t position = port_byte_in(0x3D5) << 8;
    port_byte_out(0x3D5, 15);
    position += port_byte_in(0x3D5);

    // write X at cursor
    uint16_t VGA_Position = position * 2;
    uint8_t *VGA = (uint8_t *)0xB8000;
    VGA[VGA_Position++] = 'X';
    VGA[VGA_Position++] = 0xf;
}