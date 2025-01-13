#ifndef EX24_H
#define EX24_H

#include <iostream>
#include <cassert>

class Stack
{
private:
    struct node
    {
        int data;
        node *next;

        node(int val, node *next = nullptr);
    };
    node *top;
    int size;

public:
    Stack();

    ~Stack();

    void push(int val);

    int pop();

    int getSize() const;

    void clear();

    friend std::ostream &operator<<(std::ostream &os, const Stack &stack);
};

#endif
