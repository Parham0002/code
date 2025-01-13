#include "ex21.h"
#include <iostream>
#include <cassert>

void testStack()
{
    Stack stack;

    // Test Capacity
    // assert(stack.getCapacity() == 10); // Expected Capacity: 10

    // Test push
    int valuesToPush[] = {10, 5, 34, 4, 12}; // Values to push
    for (int value : valuesToPush)
    {
        assert(stack.push(value) == true); // Expecting success on each push
    }

    // Test size after pushing
    assert(stack.getSize() == 5); // Expected size: 5

    // Test pop
    assert(stack.pop() == 12);    // Expected popped value: 12
    assert(stack.pop() == 4);     // Expected popped value: 4
    assert(stack.getSize() == 3); // Expected size: 3 after popping

    // Test isFull and isEmpty
    assert(stack.isFull() == false);  // Stack should not be full
    assert(stack.isEmpty() == false); // Stack should not be empty

    // Test clear
    stack.clear();
    assert(stack.getSize() == 0);    // Expected size: 0 after clearing
    assert(stack.isEmpty() == true); // Stack should be empty
}

int main()
{
    // Run the test
    testStack();

    std::cout << "All tests passed!" << std::endl;
    return 0;
}

/*
#include "stack.h"
#include <cassert>
#include <iostream>

static stack stck;

void test_stack_clear_push(void)
{
    for (int i = 1; i <= stack::SIZE; i++)
    {
        assert(stck.push(i));
        assert(i == stck.available());
    }

    stck.clear();
    assert(0 == stck.available());
}

void test_stack_push_pop(void)
{
    assert(stck.push(10));
    assert(1 == stck.available());

    int value = 0;
    assert(stck.pop(value));
    assert(0 == stck.available());
    assert(10 == value);
}

void test_stack_empty_full(void)
{
    int value = 0;
    assert(!stck.pop(value));
    assert(0 == value);

    for (int i = 1; i <= stack::SIZE; i++)
    {
        assert(stck.push(i));
        assert(i == stck.available());
    }

    assert(stck.isfull());
    assert(!stck.push(100));

    for (int i = stack::SIZE; i > 0; i--)
    {
        assert(stck.pop(value));
        assert(i == value);
        assert((i - 1) == stck.available());
    }

    assert(stck.isempty());
    assert(!stck.pop(value));
}

int main(void)
{
    test_stack_clear_push();
    test_stack_push_pop();
    test_stack_empty_full();

    std::cout << "All tests passed!" << std::endl;

    return 0;
}*/