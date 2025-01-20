<<<<<<< HEAD
/*
Make an uncopyable template queue class using a linked list to provide the following functions:
A function to enqueue a data element to a queue.
A function to dequeue a data element from a queue.
A function to get the number of data elements stored in a queue.
A function to clear a queue.
Test the class using assertions and ensure that all the allocated memory blocks are released.*/

#include <iostream>

template <typename t>
class queue
{
};
=======
#include <iostream>
#include <cassert>

// uncopyable class
class uncopyable
{
protected:
    uncopyable() = default;
    ~uncopyable() = default;

private:
    uncopyable(const uncopyable &) = delete;
    uncopyable &operator=(const uncopyable &) = delete;
};

// template Queue class

template <typename T>
class queue : private uncopyable
{

private:
    struct node
    {
        T data;
        node *next;
        node(const T &value) : data(value), next(nullptr) {}
    };

    node *front;
    node *rear;
    size_t count;

public:
    // constructor
    queue() : front(nullptr), rear(nullptr), count(0) {}
    // deconstructor
    ~queue()
    {
        clear();
    }

    // enqueue func
    void enqueue(const T &value)
    {
        node *newnode = new node(value);
        if (rear)
        {
            rear->next = newnode;
        }
        else
        {
            front = newnode;
        }
        rear = newnode;
        ++count;
    }

    // dequeue func
    T dequeue()
    {
        if (isEmpty())
        {
            throw std::underflow_error("queue is empty!");
        }
        node *temp = front;
        T value = temp->data;
        front = front->next;
        if (!front)
        {
            rear = nullptr;
        }
        delete temp;
        --count;
        return value;
    }
    // get the number of elements in queue
    size_t size() const
    {
        return count;
    }
    void clear()
    {
        while (!isEmpty())
        {
            dequeue();
        }
    }
    // check if queue is empty
    bool isEmpty()
    {
        return count == 0;
    }
};

int main()
{
    queue<int> q;
    // test enqueue
    q.enqueue(10);
    q.enqueue(15);
    q.enqueue(20);
    assert(q.size() == 3);

    // test dequeue
    assert(q.dequeue() == 10);
    assert(q.dequeue() == 15);
    assert(q.size() == 1);

    // test clear
    q.clear();
    assert(q.isEmpty());

    // test exception handling
    try
    {
        q.dequeue();
        assert(false); // should not reach here
    }
    catch (const std::underflow_error &e)
    {
        assert(true); // exception was correctly thrown
    }
    std::cout << "all thest passed successfully" << std::endl;
    return 0;
}
>>>>>>> 99788fd532fcad26a53bae76f90989c80f35445f
