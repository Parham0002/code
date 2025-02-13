#ifndef EX43_H
#define EX43_H

#include <stdbool.h>

// Node structure for the linked list
typedef struct Node
{
    int data;
    struct Node *next;
} Node;

// Stack structure
typedef struct Stack
{
    Node *top; // Pointer to the top node
    int size;  // Number of elements in the stack
} Stack;

// Function prototypes
Stack *create_stack();
void push(Stack *stack, int data);
int pop(Stack *stack);
int get_stack_size(Stack *stack);
void clear_stack(Stack *stack);
void destroy_stack(Stack *stack);

#endif
