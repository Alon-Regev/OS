#ifndef ORDERED_ARRAY_H
#define ORDERED_ARRAY_H

#include "types.h"

#define ASSERT(x)               \
    if (!(x))                   \
    {                           \
        PANIC("Assert failed"); \
    }

typedef void *type_t;
typedef bool_t (*lessthan_predicate_t)(type_t, type_t);

typedef struct
{
    type_t *array;
    uint32_t size;
    uint32_t max_size;
    lessthan_predicate_t lessthan_predicate;
} ordered_array_t;

// creates a new ordered array.
// input: max size, comparator
// return: new ordered array
ordered_array_t create_ordered_array(uint32_t max_size, lessthan_predicate_t lessthan_predicate);

// inserts an item into an ordered array.
// input: ordered array ptr, item to insert
// return: none
void insert_ordered_array(ordered_array_t *array, type_t item);

// removes an item into an ordered array.
// input: ordered array ptr, item index to delete
// return: none
void remove_ordered_array(ordered_array_t *array, uint32_t i);

// looks up item at index <i> of ordered array.
// input: ordered array ptr, item index to find
// return: item found
type_t lookup_ordered_array(ordered_array_t *array, uint32_t i);

#endif