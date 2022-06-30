#include "timer.h"
#include "idt.h"
#include "../drivers/ports.h"
#include "../drivers/screen.h"

uint32_t tick = 0;

void timer_callback(interrupt_handler_stack_t info)
{
    tick++;
    if(tick % 1000 == 0)
        printf("Tick: %d\n", tick);
}

void init_timer(uint32_t frequency)
{
    register_interrupt_handler(32, &timer_callback);
    
    // set frequency of PIT (Programmable Interval Timer)
    uint32_t divisor = BASE_FREQUENCY / frequency;

    uint8_t low = divisor & 0xFF;
    uint8_t high = (divisor >> 8) & 0xFF;

    // send command
    port_byte_out(PIT_COMMAND_PORT, 0x36);
    port_byte_out(PIT_DATA_PORT_CHANNEL_0, low);
    port_byte_out(PIT_DATA_PORT_CHANNEL_0, high);
}