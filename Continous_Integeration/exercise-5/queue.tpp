#include "queue.h"
#include <gtest/gtest.h>

template <typename T>
Queue<T>::Queue() : head(nullptr), tail(nullptr), count(0) {}

template <typename T>
Queue<T>::Queue(Queue &&other) noexcept : head(std::move(other.head)), tail(other.tail), count(other.count)
{
    other.tail = nullptr;
    other.count = 0;
}

template <typename T>
Queue<T> &Queue<T>::operator=(Queue &&other) noexcept
{
    if (this != &other)
    {
        clear();
        head = std::move(other.head);
        tail = other.tail;
        count = other.count;
        other.tail = nullptr;
        other.count = 0;
    }
    return *this;
}

template <typename T>
Queue<T>::~Queue()
{
    clear();
}

template <typename T>
void Queue<T>::enqueue(const T &value)
{
    auto newNode = std::make_unique<Node>(value);
    if (!tail)
    {
        head = std::move(newNode);
        tail = head.get();
    }
    else
    {
        tail->next = std::move(newNode);
        tail = tail->next.get();
    }
    ++count;
}

template <typename T>
void Queue<T>::enqueue(T &&value)
{
    auto newNode = std::make_unique<Node>(std::move(value));
    if (!tail)
    {
        head = std::move(newNode);
        tail = head.get();
    }
    else
    {
        tail->next = std::move(newNode);
        tail = tail->next.get();
    }
    ++count;
}

template <typename T>
T Queue<T>::dequeue()
{
    if (!head)
    {
        throw std::runtime_error("Queue is empty");
    }
    T value = std::move(head->data);
    head = std::move(head->next);
    if (!head)
    {
        tail = nullptr;
    }
    --count;
    return value;
}

template <typename T>
size_t Queue<T>::size() const
{
    return count;
}

template <typename T>
void Queue<T>::clear()
{
    while (head)
    {
        head = std::move(head->next);
    }
    tail = nullptr;
    count = 0;
}
