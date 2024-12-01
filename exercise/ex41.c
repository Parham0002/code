#include <stdio.h>
#include <stdlib.h>
#include "ex41.h"

// Create a new queue
Queue *create_queue()
{
    Queue *queue = (Queue *)malloc(sizeof(Queue));
    if (queue != NULL)
    {
        queue->head = NULL;
        queue->tail = NULL;
        queue->size = 0;
    }
    return queue;
}

// Enqueue a value
void enqueue(Queue *queue, int value)
{
    if (queue == NULL)
        return;

    Node *new_node = (Node *)malloc(sizeof(Node));
    if (new_node == NULL)
        return;

    new_node->data = value;
    new_node->next = NULL;

    if (queue->tail == NULL)
    {
        // Queue is empty
        queue->head = new_node;
        queue->tail = new_node;
    }
    else
    {
        queue->tail->next = new_node;
        queue->tail = new_node;
    }

    queue->size++;
}

// Dequeue a value
int dequeue(Queue *queue)
{
    int value = -1; // Default error value
    if (queue != NULL && queue->head != NULL)
    {
        Node *temp = queue->head;
        value = temp->data;
        queue->head = queue->head->next;

        if (queue->head == NULL)
        {
            // If the queue becomes empty, update rear
            queue->tail = NULL;
        }

        free(temp);
        queue->size--;
    }
    return value;
}

// Get the size of the queue
int queue_size(Queue *queue)
{
    return queue != NULL ? queue->size : 0;
}

// Clear all elements from the queue
void clear_queue(Queue *queue)
{
    if (queue != NULL)
    {
        Node *current = queue->head;
        while (current != NULL)
        {
            Node *temp = current;
            current = current->next;
            free(temp);
        }
        queue->head = NULL;
        queue->tail = NULL;
        queue->size = 0;
    }
}

// Destroy the queue and free memory
void destroy_queue(Queue *queue)
{
    if (queue != NULL)
    {
        clear_queue(queue);
        free(queue);
    }
}
