#include "ordered_array.h"
#include "../kernel/paging.h"
#include "memory.h"

int default_comparator(void* a, void* b)
{
    return *(uint32_t*)a - *(uint32_t*)b;
}

void* index(ordered_array_t* arr, uint32_t i)
{
    return (uint8_t *)arr->array + i * arr->element_size;
}

ordered_array_t create_ordered_array(uint32_t max_size, uint32_t element_size, comparator_t comparator)
{
    if (comparator == NULL)
        comparator = default_comparator;
    // create ordered array
    ordered_array_t arr = {0};
    arr.comparator = comparator;
    arr.max_size = max_size;
    arr.element_size = element_size;
    // allocate memory
    uint32_t allocated_bytes = max_size * element_size;
    arr.array = (void*)kmalloc(allocated_bytes, FALSE, NULL);
    memset(arr.array, 0, allocated_bytes);

    return arr;
}

void insert_ordered_array(ordered_array_t *array, void* item_ptr)
{
    ASSERT(array->size < array->max_size);

    // search position
    uint32_t i = find_ordered_array(array, item_ptr);

    // insert at position
    memmove(index(array, i + 1), index(array, i), (array->size - i) * array->element_size);
    memcpy(index(array, i), item_ptr, array->element_size);

    array->size++;
}

void remove_ordered_array(ordered_array_t *array, uint32_t i)
{
    ASSERT(i < array->size);
    memmove(index(array, i), index(array, i + 1), (array->size - i - 1) * array->element_size);
    array->size--;
}

void* lookup_ordered_array(ordered_array_t *array, uint32_t i)
{
    ASSERT(i < array->size);
    return index(array, i);
}

int find_ordered_array(ordered_array_t *array, void *item_ptr)
{
    if(array->size == 0)
        return 0;
    // search position with binary search
    int low = 0, high = array->size;
    while (low != high)
    {
        uint32_t mid = (low + high) / 2;
        int c = array->comparator(item_ptr, index(array, mid));
        if (c > 0)
        {
            // in higher part
            low = mid + 1;
        }
        else if(c < 0)
        {
            // in lower part
            high = mid;
        }
        else
        {
            return mid;
        }
    }

    return low;
}