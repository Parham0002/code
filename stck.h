#ifndef STCK_H
#define STCK_H

#include <stdbool.h>

#define MAX_SIZE 100

void create_stack();

bool isempty();

bool isfull();

bool stack_push(int value);

int stack_pop();

void printstack();

#endif