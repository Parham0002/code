#include "q.h"
#include <stdlib.h>
#include <stdio.h>

static int *buffer = NULL;
static int head = 0;
static int tail = 0;
static int size = 0;
static int capacity = 0;

void create_queue(int cap)
{
    capacity = cap;
    buffer = (int *)malloc(capacity * sizeof(int));
    if (buffer == NULL)
    {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    head = 0;
    tail = -1;
    size = 0;
}

bool enqueue(int value)
{
    if (is_full())
    {
        printf("Queue is full. Cannot enqueue %d.\n", value);
        return false;
    }

    tail = (tail + 1) % capacity;
    buffer[tail] = value;
    size++;
    return true;
}

bool dequeue(int *value)
{
    if (is_empty())
    {
        printf("Queue is empty. Cannot dequeue.\n");
        return false;
    }

    *value = buffer[head];

    head = (head + 1) % capacity;
    size--;
    return true;
}

bool is_empty(void)
{
    return size == 0;
}

bool is_full(void)
{
    return size == capacity;
}

void print_queue(void)
{
    if (is_empty())
    {
        printf("Queue is empty.\n");
        return;
    }

    printf("Queue elements: ");
    for (int i = 0; i < size; i++)
    {
        int index = (head + i) % capacity;
        printf("%d ", buffer[index]);
    }
    printf("\n");
}

void destroy_queue(void)
{
    free(buffer);
    buffer = NULL;
    head = 0;
    tail = -1;
    size = 0;
    capacity = 0;
    printf("The queue is detroyed!\n");
}
