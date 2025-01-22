#include "ex2move.h"

template <typename T>
Queue<T>::Queue() : head_(nullptr), tail_(nullptr), size_(0) {}

template <typename T>
Queue<T>::Queue(Queue &&other) noexcept : head_(std::move(other.head_)), tail_(other.tail_), size_(other.size_)
{
    other.tail_ = nullptr;
    other.size_ = 0;
}

template <typename T>
Queue<T> &Queue<T>::operator=(Queue &&other) noexcept
{
    if (this != &other)
    {
        clear();
        head_ = std::move(other.head_);
        tail_ = other.tail_;
        size_ = other.size_;
        other.tail_ = nullptr;
        other.size_ = 0;
    }
    return *this;
}

template <typename T>
Queue<T>::~Queue()
{
    clear();
}

template <typename T>
void Queue<T>::enqueue(const T &data)
{
    auto newNode = std::make_unique<Node>(data);
    if (!tail_)
    {
        head_ = std::move(newNode);
        tail_ = head_.get();
    }
    else
    {
        tail_->next = std::move(newNode);
        tail_ = tail_->next.get();
    }
    ++size_;
}

template <typename T>
T Queue<T>::dequeue()
{
    if (!head_)
    {
        throw QueueException("Queue is empty, cannot dequeue.");
    }

    T data = head_->data;
    head_ = std::move(head_->next);
    if (!head_)
    {
        tail_ = nullptr;
    }
    --size_;
    return data;
}

template <typename T>
size_t Queue<T>::size() const
{
    return size_;
}

template <typename T>
void Queue<T>::clear()
{
    while (head_)
    {
        head_ = std::move(head_->next);
    }
    tail_ = nullptr;
    size_ = 0;
}

template <typename T>
Queue<T>::Node::Node(const T &data) : data(data), next(nullptr) {}