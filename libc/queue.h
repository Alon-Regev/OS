#ifndef QUEUE_H
#define QUEUE_H

#include "types.h"

#define QUEUE_ERROR (char)0

typedef struct
{
    char *buffer;
    int length;
    int startIndex;
    int endIndex;
} char_queue_t;

// function adds char to the end of the queue.
// input: pointer to queue, char to add
// return: none
void enqueue(char_queue_t* queue, char c);

// function removes the first char in the queue.
// input: pointer to queue
// return: removed char
char dequeue(char_queue_t* queue);

// function checks whether a queue is empty or not
// input: queue pointer to check
// return: true if empty
bool_t empty(char_queue_t *queue);

// function checks whether a queue is full or not
// input: queue pointer to check
// return: true if full
bool_t full(char_queue_t *queue);

#endif
