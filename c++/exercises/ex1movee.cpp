/*
Implement and test an uncopyable, but movable template stack class using an array whose size is specified during creation(size shall be greater than three)
The class shall provide the following function:
A function to get size of a stack.
A function to push a data element to a stack.
A function to get number of the data elements stored in a stack.
A function to pop an element from a stack.
A function to clear a stack
Use exception handling, test the class using assertions, ensure that the dynamic memory is managed properly and the class is movable.*/

#include <iostream>
#include <cassert>
#include <stdexcept>
#include <utility>

// Template Stack class
template <typename T>
class Stack
{
private:
    T *data;
    size_t capacity;
    size_t top;

    // Disable copy constructor and copy assignment operator
    Stack(const Stack &) = delete;
    Stack &operator=(const Stack &) = delete;

public:
    // Constructor
    explicit Stack(size_t size)
    {
        if (size <= 3)
        {
            throw std::invalid_argument("Stack size must be greater than 3");
        }
        capacity = size;
        data = new T[capacity];
        top = 0;
    }

    // Move constructor
    Stack(Stack &&other) noexcept : data(nullptr), capacity(0), top(0)
    {
        *this = std::move(other);
    }

    // Move assignment operator
    Stack &operator=(Stack &&other) noexcept
    {
        if (this != &other)
        {
            delete[] data;
            data = other.data;
            capacity = other.capacity;
            top = other.top;

            other.data = nullptr;
            other.capacity = 0;
            other.top = 0;
        }
        return *this;
    }

    // Destructor
    ~Stack()
    {
        delete[] data;
    }

    // Get the size of the stack
    size_t size() const
    {
        return capacity;
    }

    // Push a data element to the stack
    void push(const T &element)
    {
        if (top >= capacity)
        {
            throw std::overflow_error("Stack overflow: cannot push element to full stack");
        }
        data[top++] = element;
    }

    // Get the number of elements stored in the stack
    size_t count() const
    {
        return top;
    }

    // Pop an element from the stack
    T pop()
    {
        if (top == 0)
        {
            throw std::underflow_error("Stack underflow: cannot pop from an empty stack");
        }
        return data[--top];
    }

    // Clear the stack
    void clear()
    {
        top = 0;
    }
};

// Test the Stack class
int main()
{
    try
    {
        // Create a stack of size 5
        Stack<int> stack(5);
        assert(stack.size() == 5);
        assert(stack.count() == 0);

        // Push elements to the stack
        stack.push(10);
        stack.push(20);
        stack.push(30);
        assert(stack.count() == 3);

        // Pop elements and verify
        assert(stack.pop() == 30);
        assert(stack.count() == 2);

        // Clear the stack
        stack.clear();
        assert(stack.count() == 0);

        // Test move semantics
        Stack<int> stack2 = std::move(stack);
        assert(stack2.size() == 5);
        assert(stack2.count() == 0);

        // Ensure original stack is empty after move
        stack2.push(50);
        assert(stack2.count() == 1);

        std::cout << "All tests passed successfully!" << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}
