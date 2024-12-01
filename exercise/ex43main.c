#include <stdio.h>
#include <assert.h>
#include "ex43.h"

int main()
{
    // Create a stack
    Stack *stack = create_stack();

    // Test push functionality
    push(stack, 10);
    push(stack, 20);
    push(stack, 30);

    // Verify the size of the stack
    assert(get_stack_size(stack) == 3);

    // Test pop functionality
    assert(pop(stack) == 30);
    assert(pop(stack) == 20);

    // Verify the size of the stack after popping
    assert(get_stack_size(stack) == 1);

    // Test clearing the stack
    clear_stack(stack);
    assert(get_stack_size(stack) == 0);

    // Test destroying the stack
    destroy_stack(stack);

    printf("All tests passed successfully.\n");

    return 0;
}
