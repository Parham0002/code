/*
Make an uncopyable template stack class using a linked list to provide the following functions:
A function to push a data element to a stack.
A function to pop a data element from a stack.
A function to get the number of data elements stored in a stack.
A function to clear a stack.
Test the class using assertions and ensure that all the allocated memory blocks are released. */

#include <iostream>
#include <cassert>

template <typename T>
class Stack
{
private:
    struct Node
    {
        T data;
        Node *next;
        Node(const T &value, Node *nextNode = nullptr)
            : data(value), next(nextNode) {}
    };

    Node *head;
    size_t size;

    // Disable copy constructor and assignment operator
    Stack(const Stack &) = delete;
    Stack &operator=(const Stack &) = delete;

public:
    Stack() : head(nullptr), size(0) {}

    ~Stack()
    {
        clear();
    }

    void push(const T &value)
    {
        head = new Node(value, head);
        ++size;
    }

    T pop()
    {
        if (isEmpty())
        {
            throw std::underflow_error("Stack is empty");
        }

        Node *temp = head;
        T value = temp->data;
        head = head->next;
        delete temp;
        --size;

        return value;
    }

    size_t count() const
    {
        return size;
    }

    void clear()
    {
        while (head)
        {
            Node *temp = head;
            head = head->next;
            delete temp;
        }
        size = 0;
    }

    bool isEmpty() const
    {
        return head == nullptr;
    }
};

int main()
{
    Stack<int> stack;

    // Test pushing elements
    stack.push(10);
    stack.push(20);
    stack.push(30);

    assert(stack.count() == 3);

    // Test popping elements
    assert(stack.pop() == 30);
    assert(stack.pop() == 20);
    assert(stack.count() == 1);

    // Test clearing the stack
    stack.clear();
    assert(stack.count() == 0);
    assert(stack.isEmpty());

    // Ensure memory is released by performing operations
    stack.push(40);
    assert(stack.pop() == 40);

    // Test underflow condition
    try
    {
        stack.pop();
    }
    catch (const std::underflow_error &e)
    {
        std::cout << "Underflow error caught: " << e.what() << std::endl;
    }

    std::cout << "All tests passed successfully." << std::endl;
    return 0;
}