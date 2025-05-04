#include "stdlib.h"
#include <stdint.h>
#include <string.h>

static size_t counter;
static void *malloc_ptr;
static uint8_t buffer[8192];
static bool current, next;
static void *pointers[STDLIB_MAX_MALLOC_CALLS];

void stdlib_init(void)
{
    counter = 0;
    malloc_ptr = buffer;
    current = next = true;
    memset(pointers, 0, sizeof(pointers));
}

void stdlib_set_malloc_status(bool first, bool second)
{
    current = first;
    next = second;
}

void *malloc(size_t size)
{
    void *ptr = NULL;

    if (counter < STDLIB_MAX_MALLOC_CALLS)
    {
        if(current){
            current = next;
            ptr = malloc_ptr;
            malloc_ptr = ((uint8_t *)malloc_ptr + size);
            pointers[counter] = ptr;
            counter++;
        }
    }

    return ptr;
}

void free(void *ptr)
{
    if (ptr != NULL)
    {
        for (size_t i = 0; i < STDLIB_MAX_MALLOC_CALLS; i++)
        {
            if (pointers[i] == ptr)
            {
                pointers[i] = NULL;
                break;
            }
        }
    }
}

bool stdlib_all_blocks_realseealed(void)
{
    bool status = true;
    for (size_t i = 0; i < STDLIB_MAX_MALLOC_CALLS; i++)
    {
        if (pointers[i] != NULL)
        {
            status = false;
            break;
        }
    }
    return status;
}