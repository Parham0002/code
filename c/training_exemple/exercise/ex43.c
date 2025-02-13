#include "ex43.h"
#include <stdlib.h>
#include <assert.h>

// Function to create a stack instance
Stack *create_stack()
{
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    stack->top = NULL; // Initially, the stack is empty
    stack->size = 0;
    return stack;
}

// Function to push a data element onto the stack
void push(Stack *stack, int data)
{
    Node *new_node = (Node *)malloc(sizeof(Node));
    assert(new_node != NULL && "Memory allocation failed");
    new_node->data = data;
    new_node->next = stack->top;
    stack->top = new_node;
    stack->size++;
}

// Function to pop a data element from the stack
int pop(Stack *stack)
{
    assert(stack->top != NULL && "Stack underflow");
    Node *temp = stack->top;
    int data = temp->data;
    stack->top = temp->next;
    free(temp);
    stack->size--;
    return data;
}

// Function to get the number of elements in the stack
int get_stack_size(Stack *stack)
{
    return stack->size;
}

// Function to clear the stack
void clear_stack(Stack *stack)
{
    while (stack->top != NULL)
    {
        Node *temp = stack->top;
        stack->top = temp->next;
        free(temp);
    }
    stack->size = 0;
}

// Function to destroy the stack and free memory
void destroy_stack(Stack *stack)
{
    clear_stack(stack);
    free(stack);
}
