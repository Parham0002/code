/**
 * @file CircularQueue.h
 * @author Parham Rezaei (knightpslow@gmail.com)
 * @brief A template-based Circular Queue implemented using a Circular Linked List.
 *
 * This class implements a circular queue where:
 * - The oldest data is overwritten when full.
 * - The queue size is defined at runtime and can be resized.
 * - It supports arithmetic types for computing the average.
 * - The queue is uncopyable (copy constructor and copy assignment are deleted).
 * - The queue is movable (move constructor and move assignment are implemented).
 *
 * @note Requires C++14 or later.
 * @date 2024-02-20
 */

#ifndef CIRCULARQUEUE_H
#define CIRCULARQUEUE_H

#include <iostream>
#include <type_traits>
#include <stdexcept>

template <typename T>
class CircularQueue
{
private:
    struct Node
    {
        T data;
        Node *next;
        Node() : data(T()), next(nullptr) {}
        Node(const T &value) : data(value), next(nullptr) {}
    };
    Node *head{nullptr};
    Node *tail{nullptr};
    size_t capacity{0};
    size_t count{0};

public:
    // Prevent copying
    CircularQueue(const CircularQueue &) = delete;
    CircularQueue &operator=(const CircularQueue &) = delete;

    // Allow moving
    CircularQueue(CircularQueue &&other) noexcept
        : head(other.head), tail(other.tail), capacity(other.capacity), count(other.count)
    {
        other.head = other.tail = nullptr;
        other.count = 0;
    }

    CircularQueue &operator=(CircularQueue &&other) noexcept
    {
        if (this != &other)
        {
            // Delete existing nodes
            this->~CircularQueue();

            // Move from other
            head = other.head;
            tail = other.tail;
            capacity = other.capacity;
            count = other.count;
            other.head = other.tail = nullptr;
            other.count = 0;
        }
        return *this;
    }

    // Constructor
    explicit CircularQueue(size_t size) : head(nullptr), tail(nullptr), capacity(size), count(0)
    {
        if (size < 3)
        {
            throw std::invalid_argument("Size must be greater than 2");
        }

        head = new (std::nothrow) Node(T());
        if (head == nullptr)
        {
            throw std::bad_alloc();
        }
        tail = head;

        for (size_t i = 1; i < size; i++)
        {
            tail->next = new (std::nothrow) Node;
            if (tail->next == nullptr)
            {
                // we need to delete from head to tail
                while (head != nullptr)
                {
                    tail = head;
                    head = head->next;
                    delete tail;
                }

                throw std::bad_alloc();
            }
            tail = tail->next;
        }

        tail->next = head;
    }
    ~CircularQueue()
    {
        for (size_t i = 0; i < capacity; ++i)
        {
            tail = head;
            head = head->next;
            delete tail;
        }
    }

    void enqueue(T value)
    {
        if (count == 0)
        {
            head->data = value;
            tail = head->next;
        }
        else if (count == capacity)
        {
            tail->data = value;
            tail = tail->next;
            head = head->next; // Move head forward when overwriting
        }
        else
        {
            tail->data = value;
            tail = tail->next;
        }

        if (count < capacity)
            count++;
    }
    T dequeue()
    {
        if (count == 0)
        {
            throw std::runtime_error("Queue is empty");
        }
        T value = head->data;
        head = head->next;
        count--;
        return value;
    }

    bool isFull() const
    {
        return count == capacity;
    }

    int size() const
    {
        return count;
    }

    void resize(size_t newSize)
    {
        if (newSize < 3)
        {
            throw std::invalid_argument("Size must be greater than 2");
        }
        while (count > newSize)
        {
            dequeue();
        }
        capacity = newSize;
    }
    
    void clear()
    {
        count = 0;
        head = tail->next;
    }

    template <typename U = T>
    typename std::enable_if<std::is_arithmetic<U>::value, double>::type getAverage() const
    {
        if (count == 0)
            return 0.0;

        double sum = 0;
        Node *current = head;
        int items = count;
        while (items > 0)
        {
            sum += current->data;
            current = current->next;
            items--;
        }
        return sum / count;
    }
};

#endif // CIRCULARQUEUE_H

