#include "stck.h"
#include <stdio.h>

int main()
{

    create_stack();

    printf("Pushing 10, 20, 30 onto the stack...\n");
    stack_push(10);
    stack_push(20);
    stack_push(30);

    printstack();

    printf("Popping from the stack...\n");
    printf("Popped: %d\n", stack_pop());

    printstack();
    printf("Checking if the stack is empty: %s\n", isempty() ? "Yes" : "No");

    printf("Popping all elements...\n");
    stack_pop();
    stack_pop();
    stack_pop();

    printf("Checking if the stack is empty: %s\n", isempty() ? "Yes" : "No");

    return 0;
}
