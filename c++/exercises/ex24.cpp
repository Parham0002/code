/*
Implement and test a stack class using a linked list to store and restore data of type int.
Test the class using assertions and ensure that all the allocated memory blocks are released.
The class shall provide the following function:
A function to push a data element to a stack.
A function to get number of the data elements stored in a stack.
A function to pop an element from a stack.
A function to clear a stack
Overload the insertion operator to print a stack to the terminal*/

#include "ex24.h"

// Node constructor
Stack::node::node(int val, node *next) : data(val), next(next) {}

// Stack constructor
Stack::Stack() : top(nullptr), size(0) {}

// Stack destructor
Stack::~Stack()
{
    clear();
}

// Push method
void Stack::push(int val)
{
    top = new node(val, top);
    ++size;
}

// Pop method
int Stack::pop()
{
    assert(top != nullptr && "Stack underflow");
    node *nodeToDelete = top;
    int value = top->data;
    top = top->next;
    delete nodeToDelete;
    --size;
    return value;
}

// Get size
int Stack::getSize() const
{
    return size;
}

// Clear the stack
void Stack::clear()
{
    while (top != nullptr)
    {
        node *nodeToDelete = top;
        top = top->next;
        delete nodeToDelete;
    }
    size = 0;
}

// Overload ostream operator
std::ostream &operator<<(std::ostream &os, const Stack &stack)
{
    Stack::node *current = stack.top;
    os << "[";
    while (current != nullptr)
    {
        os << current->data;
        current = current->next;
        if (current != nullptr)
        {
            os << ", ";
        }
    }
    os << "]";
    return os;
}
