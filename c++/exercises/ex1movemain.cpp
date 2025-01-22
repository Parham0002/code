#include "ex1move.h"
#include <iostream>
#include <cassert>

int main()
{
    try
    {
        // Create a stack of size 5
        Stack<int> stack(5);
        assert(stack.size() == 5);
        assert(stack.count() == 0);

        // Push elements to the stack
        stack.push(10);
        stack.push(20);
        stack.push(30);
        assert(stack.count() == 3);

        // Pop elements and verify
        assert(stack.pop() == 30);
        assert(stack.count() == 2);

        // Clear the stack
        stack.clear();
        assert(stack.count() == 0);

        // Test move semantics
        Stack<int> stack2 = std::move(stack);
        assert(stack2.size() == 5);
        assert(stack2.count() == 0);

        // Ensure original stack is empty after move
        stack2.push(50);
        assert(stack2.count() == 1);

        std::cout << "All tests passed successfully!" << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}
