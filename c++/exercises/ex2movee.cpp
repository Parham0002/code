
/*
Make an uncopyable, but movable template queue class using a linked list to provide the following functions:
A function to enqueue a data element to a queue.
A function to dequeue a data element from a queue.
A function to get the number of data elements stored in a queue.
A function to clear a queue.
Use exception handling when you allocate memory dynamically.
Test the class using assertions and ensure that all the allocated memory blocks are released and the class is movable.
*/ \
#include<iostream>
#include <memory>
#include <cassert>
#include <utility>
#include <exception>

// Exception class for queue-specific errors
class QueueException : public std::exception
{
public:
    explicit QueueException(const char *message) : msg_(message) {}
    const char *what() const noexcept override { return msg_; }

private:
    const char *msg_;
};

// Template Queue Class
template <typename T>
class Queue
{
public:
    Queue() : head_(nullptr), tail_(nullptr), size_(0) {}

    // Disable copy constructor and copy assignment
    Queue(const Queue &) = delete;
    Queue &operator=(const Queue &) = delete;

    // Enable move constructor
    Queue(Queue &&other) noexcept : head_(std::move(other.head_)), tail_(other.tail_), size_(other.size_)
    {
        other.tail_ = nullptr;
        other.size_ = 0;
    }

    // Enable move assignment
    Queue &operator=(Queue &&other) noexcept
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

    // Function to enqueue an element
    void enqueue(const T &data)
    {
        auto newNode = std::make_unique<Node>(data);
        if (!tail_)
        {
            // If the queue is empty
            head_ = std::move(newNode);
            tail_ = head_.get();
        }
        else
        {
            // Add to the end of the queue
            tail_->next = std::move(newNode);
            tail_ = tail_->next.get();
        }
        ++size_;
    }

    // Function to dequeue an element
    T dequeue()
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

    // Function to get the number of elements in the queue
    size_t size() const
    {
        return size_;
    }

    // Function to clear the queue
    void clear()
    {
        while (head_)
        {
            head_ = std::move(head_->next);
        }
        tail_ = nullptr;
        size_ = 0;
    }

    ~Queue()
    {
        clear();
    }

private:
    struct Node
    {
        T data;
        std::unique_ptr<Node> next;

        explicit Node(const T &data) : data(data), next(nullptr) {}
    };

    std::unique_ptr<Node> head_;
    Node *tail_;
    size_t size_;
};

int main()
{
    // Test the Queue class
    Queue<int> q;

    // Test enqueue and size
    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30);
    assert(q.size() == 3);

    // Test dequeue
    assert(q.dequeue() == 10);
    assert(q.dequeue() == 20);
    assert(q.size() == 1);

    // Test clear
    q.clear();
    assert(q.size() == 0);

    // Test exception handling
    try
    {
        q.dequeue();
    }
    catch (const QueueException &e)
    {
        std::cout << "Caught exception: " << e.what() << std::endl;
    }

    // Test move semantics
    q.enqueue(40);
    q.enqueue(50);
    Queue<int> q2 = std::move(q);
    assert(q2.size() == 2);
    assert(q.size() == 0); // Original queue should be empty after move

    assert(q2.dequeue() == 40);
    assert(q2.dequeue() == 50);

    std::cout << "All tests passed!" << std::endl;
    return 0;
}
