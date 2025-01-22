#ifndef EXMOVE2_H
#define EXMOVE2_H

#include <memory>
#include <exception>
#include <cstddef>

class QueueException : public std::exception
{
public:
    explicit QueueException(const char *message) : msg_(message) {}
    const char *what() const noexcept override { return msg_; }

private:
    const char *msg_;
};

template <typename T>
class Queue
{
public:
    Queue();
    Queue(const Queue &) = delete;
    Queue &operator=(const Queue &) = delete;
    Queue(Queue &&other) noexcept;
    Queue &operator=(Queue &&other) noexcept;
    ~Queue();

    void enqueue(const T &data);
    T dequeue();
    size_t size() const;
    void clear();

private:
    struct Node
    {
        T data;
        std::unique_ptr<Node> next;

        explicit Node(const T &data);
    };

    std::unique_ptr<Node> head_;
    Node *tail_;
    size_t size_;
};

#endif // EXMOVE2_H
