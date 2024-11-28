#include "q.h"
#include <stdio.h>
#define SIZE 5

int main(void)
{
    int cap = SIZE;
    create_queue(cap);

    enqueue(10);
    enqueue(20);
    enqueue(30);
    enqueue(40);
    enqueue(50);

    print_queue();

    enqueue(60);

    int value;
    if (dequeue(&value))
    {
        printf("Dequeued: %d\n", value);
    }

    print_queue();

    printf("Is empty: %s\n", is_empty() ? "Yes" : "No");
    printf("Is full: %s\n", is_full() ? "Yes" : "No");

    destroy_queue();

    return 0;
}
