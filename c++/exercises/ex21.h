#ifndef ex21_H
#define ex21_H

#include <iostream>

class Stack
{
public:
    static constexpr int MAX_SIZE{10};

    Stack();
    bool push(int value);
    int pop();
    int getSize() const;
    // int getCapacity() const;
    bool isFull() const;
    bool isEmpty() const;
    void clear();

private:
    int array[MAX_SIZE];
    int top;
};

#endif

/*
#ifndef STACK_H
#define STACK_H

class stack
{
public:
    static constexpr int SIZE{10};

public:
    bool push(int value);

    bool pop(int &elem);

    int available(void);

    bool isempty(void);

    bool isfull(void);

    void clear(void);

private:
    int array[SIZE]{0};
    int top{-1};
};

#endif
 */