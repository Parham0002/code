#ifndef EX41_H
#define EX41_H

typedef struct Node
{
    int data;
    struct Node *next;
} Node;

typedef struct Queue
{
    Node *head; // Points to the front of the queue
    Node *tail; // Points to the rear of the queue
    int size;   // Tracks the number of elements in the queue
} Queue;

// Function prototypes
Queue *create_queue();                 // Creates a new queue
void enqueue(Queue *queue, int value); // Enqueue a value
int dequeue(Queue *queue);             // Dequeue a value
int queue_size(Queue *queue);          // Get the size of the queue
void clear_queue(Queue *queue);        // Clear all elements from the queue
void destroy_queue(Queue *queue);      // Delete the queue and free memory

#endif
