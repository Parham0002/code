#include "ex24.h"

int main()
{
    Stack stack;

    // Test pushing elements
    stack.push(10);
    stack.push(20);
    stack.push(30);
    assert(stack.getSize() == 3);

    std::cout << "Stack after pushing elements: " << stack << std::endl;

    // Test popping elements
    assert(stack.pop() == 30);
    assert(stack.pop() == 20);
    assert(stack.getSize() == 1);

    std::cout << "Stack after popping elements: " << stack << std::endl;

    // Test clearing the stack
    stack.clear();
    assert(stack.getSize() == 0);

    std::cout << "Stack after clearing: " << stack << std::endl;

    // Test popping from an empty stack (should assert)

    // stack.pop();

    std::cout << "All tests passed successfully." << std::endl;
    return 0;
}