#ifndef STACK_H
#define STACK_H

#include <stdbool.h>
#include <stddef.h>

typedef struct {
    void (*realese)(void *);
    void *(*allocate)(size_t);

}stack_memory_t;

typedef struct stack stack_t;

void stack_init(const stack_memory_t *ptr);

stack_t *stack_create(int size);

int stack_size(stack_t *stck);

int stack_available(stack_t *stck);

bool stack_push(stack_t *stck, int data);

bool stack_pop(stack_t *stck, int *data);

bool stack_clear(stack_t *stck);

void stack_destroy(stack_t **stck);

#endif  