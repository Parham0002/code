#ifndef CIRCULARQUEUE_H
#define CIRCULARQUEUE_H

#include <iostream>
#include <type_traits>

template <typename T>
class CircularQueue
{
private:
    struct Node
    {
        T data;
        Node *next;
        Node(T value) : data(value), next(nullptr) {}
    };

    Node *head;
    Node *tail;
    int capacity;
    int count;

public:
    explicit CircularQueue(int size) : head(nullptr),
                                       tail(nullptr),
                                       capacity(size),
                                       count(0)
    {
        if (size < 3)
            throw std::invalid_argument("Size must be greater than 2");
        for (int i = 0; i < size; i++)
        {
            Node *newNode = new Node(T());
            if (!head)
            {
                head = tail = newNode;
                tail->next = head;
            }
            else
            {
                tail->next = newNode;
                tail = newNode;
                tail->next = head;
            }
        }
    }

    ~CircularQueue()
    {
        while (head && count > 0)
        {
            Node *temp = head;
            head = head->next;
            delete temp;
            count--;
        }
    }

    void enqueue(T value)
    {
        Node *newNode = new Node(value);

        if (count == 0)
        {
            head = tail = newNode;
        }
        else
        {
            tail->next = newNode;
            tail = newNode;
        }

        if (count == capacity)
        {
            Node *temp = head;
            head = head->next;
            delete temp;
        }
        else
        {
            count++;
        }
    }

    T dequeue()
    {
        if (count == 0)
        {
            throw std::runtime_error("Queue is empty");
        }

        T value = head->data;
        Node *temp = head;
        head = head->next;

        if (head == nullptr)
        {
            tail = nullptr;
        }

        delete temp;
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

    void resize(int newSize)
    {
        if (newSize < 3)
            throw std::invalid_argument("Size must be greater than 2");
        while (count > newSize)
            dequeue(); // Remove oldest elements
        capacity = newSize;
    }

    template <typename U = T>
    typename std::enable_if<std::is_arithmetic<U>::value, double>::type getAverage() const
    {
        if (count == 0)
            return 0.0;
        double sum = 0;
        Node *temp = head;
        for (int i = 0; i < count; i++)
        {
            sum += temp->data;
            temp = temp->next;
        }
        return sum / count;
    }
};

#endif
