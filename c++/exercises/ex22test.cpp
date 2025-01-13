#include "ex22.h"
#include <iostream>
#include <cassert>

void testPushAndPop()
{
    SingletonStack *stack = SingletonStack::getInstance();

    // Test push
    stack->push(1);
    stack->push(2);
    stack->push(3);

    // Verify the count
    assert(stack->getCount() == 3); // Expected output: 3

    // Test pop
    assert(stack->pop() == 3); // Expected output: 3
    assert(stack->pop() == 2); // Expected output: 2
}

void testOverflowAndUnderflow()
{
    SingletonStack *stack = SingletonStack::getInstance();

    // Push until stack is full
    for (int i = 1; i <= SingletonStack::MAX_SIZE; ++i)
    {
        stack->push(i);
    }
    assert(stack->getCount() == SingletonStack::MAX_SIZE); // Expected output: 10

    // Try to push one more element (this should overflow)
    assert(stack->push(11) == false); // Should output "Stack Overflow!"

    // Pop all elements
    while (stack->getCount() > 0)
    {
        stack->pop();
    }

    // Try to pop from an empty stack (this should underflow)
    assert(stack->pop() == -1); // Should output "Stack Underflow!"
}

void testClear()
{
    SingletonStack *stack = SingletonStack::getInstance();

    // Push some values
    stack->push(1);
    stack->push(2);
    stack->push(3);

    assert(stack->getCount() == 3); // Expected output: 3

    // Clear the stack
    stack->clear();

    assert(stack->getCount() == 0); // Expected output: 0
}
int main()
{
    // run tests
    testPushAndPop();
    testOverflowAndUnderflow();
    testClear();

    std::cout << "All tests passed!" << std::endl;
    return 0;
}