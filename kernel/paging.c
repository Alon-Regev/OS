#include "paging.h"
#include "idt.h"
#include "../libc/io.h"
#include "../libc/memory.h"

static page_directory_t *kernel_directory;
static page_directory_t *current_directory;

// --- bitset functions

static uint32_t *frame_bitset;
static uint32_t frame_count;

void set_frame_bit(uint32_t frameAddress)
{
    uint32_t frame = frameAddress / 0x1000;
    uint32_t index = frame / 32;
    uint32_t offset = frame % 32;
    frame_bitset[index] |= 0x1 << offset;
}

void clear_frame_bit(uint32_t frameAddress)
{
    uint32_t frame = frameAddress / 0x1000;
    uint32_t index = frame / 32;
    uint32_t offset = frame % 32;
    frame_bitset[index] &= ~(0x1 << offset);
}

bool_t test_frame_bit(uint32_t frameAddress)
{
    uint32_t frame = frameAddress / 0x1000;
    uint32_t index = frame / 32;
    uint32_t offset = frame % 32;
    return frame_bitset[index] & (0x1 << offset);
}

// returns first free frame.
// input: none
// return: frame number. -1 if no free frame.
uint32_t first_frame()
{
    // go over bitset
    for (int i = 0; i < frame_count / 32; i++)
    {
        if (frame_bitset[i] == 0xFFFFFFFF)
            continue;
        // there's a 0 bit
        for (int j = 0; j < 32; j++)
        {
            if (!(frame_bitset[i] & (1 << j)))
                return 32 * i + j;
        }
    }
    return (uint32_t)-1;
}

// --- basic kernel malloc

static uint32_t placement_address = 0x10000;
uint32_t kmalloc(uint32_t size, bool_t align, uint32_t *physical)
{
    // align placement address (if needed)
    if (align && (placement_address & 0xFFF))
    {
        placement_address &= ~0xFFF;
        placement_address += 0x1000;
    }
    if (physical)
    {
        *physical = placement_address;
    }
    uint32_t ret = placement_address;
    placement_address += size;
    return ret;
}

// --- paging functions

void init_paging()
{
    uint32_t memoryEnd = 0x1000000;
    frame_count = memoryEnd / 0x1000;

    // allocate <frame_count> bits
    frame_bitset = (uint32_t *)kmalloc(frame_count / 8, FALSE, NULL);
    memset(frame_bitset, 0, frame_count / 8);

    // create page directory
    uint32_t physical;
    kernel_directory = (page_directory_t *)kmalloc(sizeof(page_directory_t), TRUE, &physical);
    memset(kernel_directory, 0, sizeof(page_directory_t));
    kernel_directory->physicalAddress = physical;
    current_directory = kernel_directory;

    // identity mapping
    int i = 0;
    while (i < IDENTITY_MAPPING_LIMIT)
    {
        allocate_frame(get_page(i, TRUE, kernel_directory), FALSE, FALSE);
        i += 0x1000;
    }

    // page fault handler
    register_interrupt_handler(14, page_fault);

    // enable paging
    switch_page_directory(kernel_directory);
}

void switch_page_directory(page_directory_t *directory)
{
    current_directory = directory;
    asm volatile("mov %0, %%cr3" ::"r"(&directory->tablesPhysicalAddresses));
    // set flag on cr0
    uint32_t cr0;
    asm volatile("mov %%cr0, %0"
                 : "=r"(cr0));
    cr0 |= 0x80000000;
    asm volatile("mov %0, %%cr0" ::"r"(cr0));
}

page_t *get_page(uint32_t address, bool_t make, page_directory_t *directory)
{
    address /= 0x1000;
    // get page table
    uint32_t pageTableIndex = address / 1024;
    if (directory->tables[pageTableIndex])
    {
        return &directory->tables[pageTableIndex]->pages[address % 1024];
    }
    else if (make)
    {
        uint32_t physicalAddr;
        directory->tables[pageTableIndex] = (page_table_t *)kmalloc(sizeof(page_table_t), TRUE, &physicalAddr);
        memset(directory->tables[pageTableIndex], 0, sizeof(page_table_t));
        directory->tablesPhysicalAddresses[pageTableIndex] = (physicalAddr | 0x7); // present, rw, us
        return &directory->tables[pageTableIndex]->pages[address % 1024];
    }
    else
    {
        return NULL;
    }
}

void page_fault(interrupt_handler_stack_t info)
{
    uint32_t faultAddress;
    // read address from cr2
    asm volatile("mov %%cr2, %0"
                 : "=r"(faultAddress));

    // check error bits
    printf("Page fault! ( ");
    if (!(info.errorCode & 0x1))
    {
        printf("present ");
    }
    if (info.errorCode & 0x2)
    {
        printf("read-only ");
    }
    if (info.errorCode & 0x4)
    {
        printf("user-mode ");
    }
    if (info.errorCode & 0x10)
    {
        printf("reserved ");
    }
    printf(") at 0x%x\n", faultAddress);
    PANIC("Page fault");
}

void allocate_frame(page_t *page, bool_t isKernel, bool_t isWriteable)
{
    if (page->frame != 0)
    {
        // already allocated
        return;
    }
    uint32_t frame = first_frame();
    if (frame == (uint32_t)-1)
    {
        // no free frame
        PANIC("No Free Frames");
    }
    // allocate frame
    set_frame_bit(frame * 0x1000);
    page->present = 1;
    page->rw = isWriteable ? 1 : 0;
    page->user = isKernel ? 0 : 1;
    page->frame = frame;
}

void free_frame(page_t *page)
{
    uint32_t frame = page->frame;
    if (frame == 0)
    {
        // not allocated
        return;
    }
    clear_frame_bit(frame * 0x1000);
    page->frame = 0x0;
}