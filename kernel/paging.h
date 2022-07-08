#ifndef PAGING_H
#define PAGING_H

#include "../libc/types.h"
#include "idt.h"
#include "../libc/io.h"

#define IDENTITY_MAPPING_LIMIT 0x100000

#define PANIC(msg)                                          \
    printf("PANIC (%s) at %s:%d", msg, __FILE__, __LINE__); \
    while (TRUE)

typedef struct
{
    uint32_t present : 1;  // Page present in memory
    uint32_t rw : 1;       // Read-only if clear, readwrite if set
    uint32_t user : 1;     // Supervisor level only if clear
    uint32_t accessed : 1; // Has the page been accessed since last refresh?
    uint32_t dirty : 1;    // Has the page been written to since last refresh?
    uint32_t unused : 7;   // Amalgamation of unused and reserved bits
    uint32_t frame : 20;   // Frame address (shifted right 12 bits)
} page_t;

typedef struct
{
    page_t pages[1024];
} page_table_t;

typedef struct
{
    page_table_t *tables[1024];
    uint32_t tablesPhysicalAddresses[1024];
    uint32_t physicalAddress; // address of tablesPhysicalAddresses
} page_directory_t;

// function initializes paging.
// input: none
// return: none
void init_paging();

// function switches current page directory
// input: none
// return: none
void switch_page_directory(page_directory_t *directory);

// function returns pointer to requested page
// input: address, whether to create missing pages or not, page directory ptr
// return: pointer to page
page_t *get_page(uint32_t address, bool_t make, page_directory_t *directory);

// page fault handler
void page_fault(interrupt_handler_stack_t* info);

// alocate a free frame
// input: page pointer to fill, flags (kernel, writeable)
// return: none
void allocate_frame(page_t *page, bool_t isKernel, bool_t isWriteable);

// deallocates a frame
// input: page pointer to deallocate
// return: none
void free_frame(page_t *page);

// basic memory allocation for the kernel.
// input: malloc size, align to page size or not, pointer to store physical address in
// return: virtual address to use
uint32_t kmalloc(uint32_t size, bool_t align, uint32_t *physical);

#endif