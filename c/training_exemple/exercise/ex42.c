#include "ex42.h"
#include <stdlib.h>
#include <assert.h>

// Function to create a stack instance
Stack *create_stack(int length)
{
    assert(length > 0 && "Stack length must be greater than zero");
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    stack->array = (uint8_t *)malloc(length * sizeof(uint8_t));
    stack->top = -1; // Indicates the stack is empty
    stack->max_length = length;
    return stack;
}

// Function to push a data element onto the stack
void push(Stack *stack, uint8_t data)
{
    assert(stack->top < stack->max_length - 1 && "Stack overflow");
    stack->array[++stack->top] = data;
}

// Function to pop a data element from the stack
uint8_t pop(Stack *stack)
{
    assert(stack->top >= 0 && "Stack underflow");
    return stack->array[stack->top--];
}

// Function to get the number of elements in the stack
int get_stack_size(Stack *stack)
{
    return stack->top + 1;
}

// Function to get the maximum length of the stack
int get_stack_length(Stack *stack)
{
    return stack->max_length;
}

// Function to clear the stack
void clear_stack(Stack *stack)
{
    stack->top = -1; // Reset the top index
}

// Function to destroy the stack and free memory
void destroy_stack(Stack *stack)
{
    free(stack->array);
    free(stack);
}
