#ifndef EX42_H
#define EX42_H

#include <stdint.h>

// Stack structure
typedef struct
{
    uint8_t *array; // Pointer to the stack array
    int top;        // Index of the top element in the stack
    int max_length; // Maximum length of the stack
} Stack;

// Function prototypes
Stack *create_stack(int length);
void push(Stack *stack, uint8_t data);
uint8_t pop(Stack *stack);
int get_stack_size(Stack *stack);
int get_stack_length(Stack *stack);
void clear_stack(Stack *stack);
void destroy_stack(Stack *stack);

#endif
