#ifndef EX25_H
#define EX25_H

#include <iostream>
#include <cassert>

// Uncopyable Queue class
class Queue
{
private:
    struct node
    {
        int data;
        node *next;

        node(int val, node *next = nullptr);
    };

    node *front;
    node *rear;
    int size;

    // Disable copy constructor and copy assignment
    Queue(const Queue &) = delete;
    Queue &operator=(const Queue &) = delete;

public:
    Queue();               // Constructor
    ~Queue();              // Destructor
    void enqueue(int val); // Add element to queue
    int dequeue();         // Remove element from queue
    int getSize() const;   // Get size of queue
    void clear();          // Clear the queue

    friend std::ostream &operator<<(std::ostream &os, const Queue &queue);
};

#endif // EX25_H
