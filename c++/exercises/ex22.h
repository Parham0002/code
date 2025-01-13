#ifndef EX22_H
#define EX22_H

#include <iostream>

class SingletonStack
{
public:
    static constexpr int MAX_SIZE{10}; // compile-time constant

    static SingletonStack *getInstance();

    bool push(int value);
    int getCount();
    int pop();

    void clear();

private:
    static SingletonStack *instance;
    int array[MAX_SIZE];
    int top;

    // Private constructor to prevent instantiation
    SingletonStack();

    // Delete copy constructor and assignment operator to make class uncopyable
    SingletonStack(const SingletonStack &) = delete;
    SingletonStack &operator=(const SingletonStack &) = delete;
};

#endif // EX22_H
