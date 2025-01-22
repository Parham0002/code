#include "ex1move.h"
#include <utility>

// Constructor
template <typename T>
Stack<T>::Stack(size_t size)
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
template <typename T>
Stack<T>::Stack(Stack &&other) noexcept : data(nullptr), capacity(0), top(0)
{
    *this = std::move(other);
}

// Move assignment operator
template <typename T>
Stack<T> &Stack<T>::operator=(Stack &&other) noexcept
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
template <typename T>
Stack<T>::~Stack()
{
    delete[] data;
}

// Get the size of the stack
template <typename T>
size_t Stack<T>::size() const
{
    return capacity;
}

// Push a data element to the stack
template <typename T>
void Stack<T>::push(const T &element)
{
    if (top >= capacity)
    {
        throw std::overflow_error("Stack overflow: cannot push element to full stack");
    }
    data[top++] = element;
}

// Get the number of elements stored in the stack
template <typename T>
size_t Stack<T>::count() const
{
    return top;
}

// Pop an element from the stack
template <typename T>
T Stack<T>::pop()
{
    if (top == 0)
    {
        throw std::underflow_error("Stack underflow: cannot pop from an empty stack");
    }
    return data[--top];
}

// Clear the stack
template <typename T>
void Stack<T>::clear()
{
    top = 0;
}