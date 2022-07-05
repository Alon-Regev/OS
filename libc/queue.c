#include "queue.h"

int queueIndex(char_queue_t* queue, int index)
{
    return (index + queue->length) % queue->length;
}

void enqueue(char_queue_t* queue, char c)
{
    if (full(queue))
    {
        // move start
        queue->startIndex = queueIndex(queue, queue->startIndex + 1);
    }
    // add to end
    queue->buffer[queue->endIndex] = c;
    queue->endIndex = queueIndex(queue, queue->endIndex + 1);
}

char dequeue(char_queue_t* queue)
{
    if(!empty(queue))
    {
        char c = queue->buffer[queue->startIndex];
        // decrement start
        queue->startIndex = queueIndex(queue, queue->startIndex + 1);
        return c;
    }
    // empty queue
    return QUEUE_ERROR;
}

void erase(char_queue_t *queue)
{
    if(empty(queue))
        return;

    queue->endIndex = queueIndex(queue, queue->endIndex - 1);
}

bool_t empty(char_queue_t *queue)
{
    return queue->startIndex == queue->endIndex;
}

bool_t full(char_queue_t *queue)
{
    return queueIndex(queue, queue->endIndex + 1) == queue->startIndex;
}

void flush_queue(char_queue_t *queue)
{
    queue->startIndex = queue->endIndex;
}