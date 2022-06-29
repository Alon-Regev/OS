#include "idt.h"
#include "../helpers/string.h"

idt_entry idt_entries[256] = {0};
idt_ptr idt_pointer;

void init_idt()
{
    idt_pointer.limit = sizeof(idt_entry) * 256 - 1;
    idt_pointer.addr = (uint32_t)idt_entries;

    // setup ISRs
    memset(idt_entries, 0, sizeof(idt_entry) * 256);

    // load new idt
    load_idt((uint32_t)&idt_pointer);
}

void idt_set_gate(uint8_t num, uint32_t addr, uint16_t selector, uint8_t flags)
{
    
}