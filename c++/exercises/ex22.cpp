/*
Implement and test an uncopyable singleton stack class using an array of type int whose size is a compile-time constant.
The singleton class shall provide the following function:
A function to push a data element to the stack.
A function to get number of the data elements stored in the stack.
A function to pop an element from the stack.
A function to clear the stack*/

#include "ex22.h"

// Initialize static instance pointer
SingletonStack *SingletonStack::instance = nullptr;

SingletonStack::SingletonStack() : top(-1) {}

SingletonStack *SingletonStack::getInstance()
{
    if (instance == nullptr)
    {
        instance = new SingletonStack();
    }
    return instance;
}

bool SingletonStack::push(int value)
{
    if (top >= MAX_SIZE - 1)
    {
        return false;
    }
    array[++top] = value;
    return true;
}

int SingletonStack::getCount()
{
    return top + 1;
}

int SingletonStack::pop()
{
    if (top < 0)
    {
        return -1;
    }
    return array[top--];
}

void SingletonStack::clear()
{
    top = -1;
}
