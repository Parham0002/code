#include "ex25.h"

// Node constructor
Queue::node::node(int val, node *next) : data(val), next(next) {}

// Queue constructor
Queue::Queue() : front(nullptr), rear(nullptr), size(0) {}

// Queue destructor
Queue::~Queue()
{
    clear();
}

// Enqueue: Add element to the rear of the queue
void Queue::enqueue(int val)
{
    node *newNode = new node(val);
    if (rear != nullptr)
    {
        rear->next = newNode;
    }
    rear = newNode;
    if (front == nullptr)
    {
        front = rear;
    }
    ++size;
}

// Dequeue: Remove element from the front of the queue
int Queue::dequeue()
{
    assert(front != nullptr && "Queue underflow");
    node *nodeToDelete = front;
    int value = front->data;
    front = front->next;
    if (front == nullptr)
    {
        rear = nullptr; // If queue becomes empty, reset rear
    }
    delete nodeToDelete;
    --size;
    return value;
}

// Get size of the queue
int Queue::getSize() const
{
    return size;
}

// Clear the queue
void Queue::clear()
{
    while (front != nullptr)
    {
        node *nodeToDelete = front;
        front = front->next;
        delete nodeToDelete;
    }
    rear = nullptr;
    size = 0;
}

// Overload ostream operator for printing the queue
std::ostream &operator<<(std::ostream &os, const Queue &queue)
{
    Queue::node *current = queue.front;
    os << "[";
    while (current != nullptr)
    {
        os << current->data;
        current = current->next;
        if (current != nullptr)
        {
            os << ", ";
        }
    }
    os << "]";
    return os;
}
