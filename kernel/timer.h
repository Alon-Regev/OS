#ifndef TIMER_H
#define TIMER_H

#include "../libc/types.h"

#define BASE_FREQUENCY 1193180
#define TIMER_IRQ 0

#define PIT_COMMAND_PORT 0x43
#define PIT_DATA_PORT_CHANNEL_0 0x40

// function initializes timer to a certain frequency.
// input: frequency (in Hz)
// return: none
void init_timer(uint32_t frequency);

#endif