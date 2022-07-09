#ifndef ORDERED_ARRAY_H
#define ORDERED_ARRAY_H

#include "types.h"

#define ASSERT(x)               \
    if (!(x))                   \
    {                           \
        PANIC("Assert failed"); \
    }

typedef int (*comparator_t)(void*, void*);

typedef struct
{
    void *array;
    uint32_t size;
    uint32_t max_size;
    uint32_t element_size;
    comparator_t comparator;
} ordered_array_t;

// creates a new ordered array.
// input: max size, comparator
// return: new ordered array
ordered_array_t create_ordered_array(uint32_t max_size, uint32_t element_size, comparator_t comparator);

// inserts an item into an ordered array.
// input: ordered array ptr, ptr to item to insert
// return: none
void insert_ordered_array(ordered_array_t *array, void* item_ptr);

// removes an item into an ordered array.
// input: ordered array ptr, item index to delete
// return: none
void remove_ordered_array(ordered_array_t *array, uint32_t i);

// looks up item at index <i> of ordered array.
// input: ordered array ptr, item index to find
// return: ptr to item found
void* lookup_ordered_array(ordered_array_t *array, uint32_t i);

// finds item <x> closest to item <i> (x >= i)
// input: array ptr, item to compare to
// output: index of closest item
int find_ordered_array(ordered_array_t *array, void *item_ptr);

#endif