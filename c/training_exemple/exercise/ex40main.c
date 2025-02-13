#include <stdio.h>
#include <assert.h>
#include "ex40.h"

int main()
{
    // Create a new linked list
    linklist *list = create();
    assert(size(list) == 0);

    // Insert nodes
    insert(list, 10);
    insert(list, 5);
    insert(list, 20);
    insert(list, 15);
    assert(size(list) == 4);

    // Check sorted order and uniqueness
    assert(nth(list, 0) == 5);
    assert(nth(list, 1) == 10);
    assert(nth(list, 2) == 15);
    assert(nth(list, 3) == 20);

    // Test search
    assert(search(list, 10) == 1);
    assert(search(list, 30) == 0);

    // Change a value
    change(list, 10, 25);
    assert(search(list, 10) == 0);
    assert(search(list, 25) == 1);

    // Delete a node
    deletee(list, 5);
    assert(search(list, 5) == 0);
    assert(size(list) == 3);

    // Destroy the list
    destroy(list);

    printf("All tests passed!\n");
    return 0;
}
