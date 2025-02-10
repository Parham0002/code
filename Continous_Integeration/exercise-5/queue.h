#ifndef QUEUE_H
#define QUEUE_H

#include <memory>    // For std::unique_ptr
#include <stdexcept> // For std::runtime_error

template <typename T>
class Queue
{
private:
    struct Node
    {
        T data;
        std::unique_ptr<Node> next;

        Node(const T &value) : data(value), next(nullptr) {}
        Node(T &&value) : data(std::move(value)), next(nullptr) {}
    };

    std::unique_ptr<Node> head;
    Node *tail;
    size_t count;

    Queue(const Queue &) = delete;
    Queue &operator=(const Queue &) = delete;

public:
    Queue();
    Queue(Queue &&other) noexcept;
    Queue &operator=(Queue &&other) noexcept;
    ~Queue();

    void enqueue(const T &value);
    void enqueue(T &&value);
    T dequeue();
    size_t size() const;
    void clear();
};

#include "queue.tpp"

#endif // QUEUE_H
