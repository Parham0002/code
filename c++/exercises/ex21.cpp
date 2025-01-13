/*
Implement and test a stack class using an array of type int whose size is a compile-time constant.
The class shall provide the following function:
A function to push a data element to a stack.
A function to get number of the data elements stored in a stack.
A function to pop an element from a stack.
A function to check if a stack is full or not.
A function to check if a stack is empty or not
A function to clear a stack*/

#include "ex21.h"

Stack::Stack() : top(-1) {}

bool Stack::push(int value)
{
    bool status = false;
    if (isFull())
    {
        std::cout << "Stack Overflow!" << std::endl;
        status = false;
    }
    array[++top] = value;
    status = true;
    return status;
}

int Stack::pop()
{
    if (isEmpty())
    {
        std::cout << "Stack Underflow!" << std::endl;
        exit(1);
    }
    return array[top--];
}

int Stack::getSize() const
{
    return top + 1;
}

// int Stack::getCapacity() const
//{
// return MAX_SIZE;
//}

bool Stack::isFull() const
{
    return top >= MAX_SIZE - 1;
}

bool Stack::isEmpty() const
{
    return top < 0;
}

void Stack::clear()
{
    top = -1;
}

/*
#include "stack.h"

bool stack::push(int value)
{
    bool status = false;

    if (top < SIZE - 1)
    {
        top++;
        status = true;
        array[top] = value;
    }

    return status;
}

bool stack::pop(int &elem)
{
    bool status = false;

    if (top > -1)
    {
        elem = array[top];
        top--;
        status = true;
    }

    return status;
}

int stack::available(void)
{
    return (top + 1);
}

bool stack::isempty(void)
{
    return (top == -1);
}

bool stack::isfull(void)
{
    return (top == SIZE - 1);
}

void stack::clear(void)
{
    top = -1;
}
*/