#include "stck.h"
#include <stdlib.h>
#include <stdio.h>

int stack[MAX_SIZE];
int top = -1;

void create_stack()
{
    top = -1;
}

bool isempty()
{
    return top == -1;
}

bool isfull()
{
    return top == MAX_SIZE - 1;
}

bool stack_push(int value)
{
    if (isfull())
    {
        printf("Stack Overflow! Cannot add more elements.\n");
        return false;
    }
    stack[++top] = value;
    return true;
}

int stack_pop()
{
    if (isempty())
    {
        printf("Stack Underflow! The stack is empty.\n");
        exit(EXIT_FAILURE);
    }
    return stack[top--];
}

void printstack()
{
    if (isempty())
    {
        printf("The stack is empty.\n");
        return;
    }
    printf("Stack elements: ");
    for (int i = 0; i <= top; i++)
    {
        printf("%d ", stack[i]);
    }
    printf("\n");
}