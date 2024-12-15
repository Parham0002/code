#include <stdio.h>
#include "ex42.h"

int main()
{
    // Create a stack of length 5
    Stack *stack = create_stack(5);

    // Push elements onto the stack
    push(stack, 10);
    push(stack, 20);
    push(stack, 30);

    // Get and print the stack size
    printf("Stack size: %d\n", get_stack_size(stack));

    // Pop and print elements from the stack
    printf("Popped element: %d\n", pop(stack));
    printf("Popped element: %d\n", pop(stack));

    // Print the current stack size
    printf("Stack size after popping: %d\n", get_stack_size(stack));

    // Clear the stack
    clear_stack(stack);
    printf("Stack size after clearing: %d\n", get_stack_size(stack));

    // Destroy the stack
    destroy_stack(stack);

    return 0;
}
