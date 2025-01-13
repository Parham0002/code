#include "ex25.h"

int main()
{
    Queue queue;

    // Test enqueue operation
    queue.enqueue(10);
    queue.enqueue(20);
    queue.enqueue(30);
    assert(queue.getSize() == 3);

    std::cout << "Queue after enqueue operations: " << queue << std::endl;

    // Test dequeue operation
    assert(queue.dequeue() == 10);
    assert(queue.dequeue() == 20);
    assert(queue.getSize() == 1);

    std::cout << "Queue after dequeue operations: " << queue << std::endl;

    // Test clearing the queue
    queue.clear();
    assert(queue.getSize() == 0);

    std::cout << "Queue after clearing: " << queue << std::endl;

    // Test dequeue from an empty queue (should assert)
    // Uncomment the line below to test assertion failure
    // queue.dequeue();

    std::cout << "All tests passed successfully." << std::endl;
    return 0;
}
