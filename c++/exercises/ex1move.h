#ifndef EX1MOVE_H
#define EX1MOVE_H

#include <cstddef>
#include <stdexcept>

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
    explicit Stack(size_t size);

    // Move constructor
    Stack(Stack &&other) noexcept;

    // Move assignment operator
    Stack &operator=(Stack &&other) noexcept;

    // Destructor
    ~Stack();

    // Get the size of the stack
    size_t size() const;

    // Push a data element to the stack
    void push(const T &element);

    // Get the number of elements stored in the stack
    size_t count() const;

    // Pop an element from the stack
    T pop();

    // Clear the stack
    void clear();
};

#include "ex1move.tpp" // Include template implementation

#endif // EXMOVE1_H
