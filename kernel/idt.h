#ifndef IDT_H
#define IDT_H

#include "../libc/types.h"

#define KERNEL_CS 0x08
#define IDT_ENTRY_FLAGS 0x8E

#define IRQ(n) (n+32)

// type for the stack's state when entering the interrupt handler
typedef struct
{
    uint32_t ds;
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax; // pusha
    uint32_t interruptNumber, errorCode;            // interrupt info
    uint32_t eip, cs, eflags, user_esp, ss;         // pushed by processor
} interrupt_handler_stack_t;

typedef void (*isr_t)(interrupt_handler_stack_t*);

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

// function handles all interrupts.
// input: different data pushed to stack (interrupt_handler_stack_t)
// return: none
void isr_handler(interrupt_handler_stack_t info);

// function handlers all irq interrupts.
// input: different data pushed to stack (interrupt_handler_stack_t)
// return: none
void irq_handler(interrupt_handler_stack_t info);

// function sets up new interrupt handler.
// input: interruptNumber, handler
// return: none
void register_interrupt_handler(uint8_t interruptNumber, isr_t handler);

// Interrupt service routines
extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();

extern void irq0();
extern void irq1();
extern void irq2();
extern void irq3();
extern void irq4();
extern void irq5();
extern void irq6();
extern void irq7();
extern void irq8();
extern void irq9();
extern void irq10();
extern void irq11();
extern void irq12();
extern void irq13();
extern void irq14();
extern void irq15();

#endif