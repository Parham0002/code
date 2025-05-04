#ifndef STDILIB_H
#define STDLIB_H

#include <stddef.h>
#include <stdbool.h>

#define STDLIB_MAX_MALLOC_CALLS 16U

void stdlib_init(void);

void *malloc(size_t size);

void free(void *ptr);

void stdlib_set_malloc_status(bool first, bool second);

bool stdlib_all_blocks_realseealed(void);

#endif