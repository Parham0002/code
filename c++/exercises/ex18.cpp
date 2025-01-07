/*
Make a multiple instance stack using a fixed size array of type int.
The stack shall be tested using assertion and provide the following functions:
A function to create a stack.
A function to push a data element a stack.
A function to get number of the data elements stored in a stack.
A function to pop an element from a stack.
A function to clear a stack
A function to destroy a stack*/
#include <iostream>
#include <cassert>

class stack
{
private:
    int *array;
    int top;
    int maxsize;

public:
    stack(int size)
    {

        maxsize = size;
        array = new int[maxsize];
        top = -1;
    }

    ~stack()
    {
        destroy();
    }

    void push(int value)
    {
        if (top >= maxsize - 1)
        {
            std::cout << "Stack Overflow!" << std::endl;
            return;
        }
        array[++top] = value;
    }
    int pop()
    {
        if (top < 0)
        {
            std::cout << "Stack Underflow!" << std::endl;
            return -1;
        }
        return array[top--];
    }

    int getelements() const
    {

        return top + 1;
    }

    void clear()
    {

        top = -1;
    }

    void destroy()
    {
        if (array)
        {
            delete[] array;
            array = nullptr;
        }
        top = -1;
        maxsize = 0;
    }
};

void teststack()
{
    stack stack(5);

    assert(stack.getelements() == 0);

    stack.push(10);
    stack.push(20);
    stack.push(30);
    assert(stack.getelements() == 3);

    assert(stack.pop() == 30);
    assert(stack.pop() == 20);
    assert(stack.getelements() == 1);

    stack.clear();
    assert(stack.getelements() == 0);

    assert(stack.pop() == -1);

    stack.push(1);
    stack.push(2);
    stack.push(3);
    stack.push(4);
    stack.push(5);
    stack.push(6);

    assert(stack.getelements() == 5);

    std::cout << "All tests passed!" << std::endl;
}

int main()
{
    teststack();
    return 0;
}