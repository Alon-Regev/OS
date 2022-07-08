#include "ordered_array.h"
#include "../kernel/paging.h"
#include "memory.h"

bool_t default_lessthan_predicate(type_t a, type_t b)
{
    return a < b ? TRUE : FALSE;
}

ordered_array_t create_ordered_array(uint32_t max_size, lessthan_predicate_t lessthan_predicate)
{
    if (lessthan_predicate == NULL)
        lessthan_predicate = default_lessthan_predicate;
    // create ordered array
    ordered_array_t arr = {0};
    arr.lessthan_predicate = lessthan_predicate;
    arr.max_size = max_size;
    // allocate memory
    uint32_t allocated_bytes = max_size * sizeof(type_t);
    arr.array = (type_t *)kmalloc(allocated_bytes, FALSE, NULL);
    memset(arr.array, 0, allocated_bytes);

    return arr;
}

void insert_ordered_array(ordered_array_t *array, type_t item)
{
    ASSERT(array->size < array->max_size);

    // search position (improvement: binary search)
    int i = 0;
    while (i < array->size && array->lessthan_predicate(item, array->array[i]))
    {
        i++;
    }

    // insert at position
    memmove(array->array + i + 1, array->array + i, (array->size - i) * sizeof(type_t));
    array->array[i] = item;

    array->size++;
}

void remove_ordered_array(ordered_array_t *array, uint32_t i)
{
    ASSERT(i < array->size);
    memmove(array->array + i, array->array + i + 1, (array->size - i - 1) * sizeof(type_t));
    array->size--;
}

type_t lookup_ordered_array(ordered_array_t *array, uint32_t i)
{
    ASSERT(i < array->size);
    return array->array[i];
}