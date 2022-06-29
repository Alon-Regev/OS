#ifndef IDT_H
#define IDT_H

#include "../helpers/int_types.h"

#define KERNEL_CS 0x08
#define IDT_ENTRY_FLAGS 0x8E

// interrupt descriptor table entry
struct idt_entry_struct
{
    uint16_t addrLow;
    uint16_t segmentSelector;
    uint8_t zero;
    uint8_t flags;
    uint16_t addrHigh;
} __attribute__((packed));
typedef struct idt_entry_struct idt_entry;

// idt pointer struct suitable for 'lidt' instruction
struct idt_ptr_struct
{
   uint16_t limit;
   uint32_t addr;
} __attribute__((packed));
typedef struct idt_ptr_struct idt_ptr;

// function loads an new idt.
// input: idt pointer
// return: none
extern void load_idt(uint32_t addr);

// function initalized interrupt descriptor table.
// input: none
// return: none
void init_idt();

// function sets values of a specific idt entry.
// input: interrupt number, values to fill entry.
// return: none
void idt_set_gate(uint8_t num, uint32_t addr, uint16_t selector, uint8_t flags);

#endif