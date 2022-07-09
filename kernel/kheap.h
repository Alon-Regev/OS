#ifndef KHEAP_H
#define KHEAP_H

#include "../libc/ordered_array.h"

#define KHEAP_START 0x100000

typedef struct
{
    uint32_t address;
    uint32_t size;
} heap_block_t;

typedef struct
{
    ordered_array_t index;
    uint32_t start_address;
    uint32_t end_address;
    uint32_t max_address;
    bool_t supervisor;
    bool_t readonly;
} heap_t;

heap_t *create_heap(uint32_t start, uint32_t end, uint32_t max, bool_t supervisor, bool_t readonly);

void *heap_allocate(heap_t *heap, uint32_t size, bool_t page_align);

void heap_free(heap_t *heap, void *ptr);

#endif