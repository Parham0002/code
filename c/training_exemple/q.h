#ifndef Q_H
#define Q_H

#include <stdbool.h>

void create_queue(int capacity);

bool enqueue(int value);

bool dequeue(int *value);

bool is_empty(void);

bool is_full(void);

void print_queue(void);

void destroy_queue(void);

#endif
