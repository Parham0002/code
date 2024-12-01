#include <stdio.h>
#include <assert.h>
#include "ex41.h"

int main()
{
    // Create a queue
    Queue *queue = create_queue();
    assert(queue_size(queue) == 0);

    // Enqueue values
    enqueue(queue, 10);
    enqueue(queue, 20);
    enqueue(queue, 30);
    assert(queue_size(queue) == 3);

    // Dequeue values
    assert(dequeue(queue) == 10);
    assert(queue_size(queue) == 2);

    assert(dequeue(queue) == 20);
    assert(queue_size(queue) == 1);

    // Enqueue more values
    enqueue(queue, 40);
    enqueue(queue, 50);
    assert(queue_size(queue) == 3);

    // Dequeue the rest
    assert(dequeue(queue) == 30);
    assert(dequeue(queue) == 40);
    assert(dequeue(queue) == 50);
    assert(queue_size(queue) == 0);

    // Clear and destroy the queue
    enqueue(queue, 60);
    enqueue(queue, 70);
    clear_queue(queue);
    assert(queue_size(queue) == 0);

    destroy_queue(queue);

    printf("All tests passed!\n");
    return 0;
}
