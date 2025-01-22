#include "ex2move.h"
#include <iostream>
#include <cassert>
#include <queue>

int main()
{
    std::queue<int> q;

    // Test enqueue and size
    q.push(10);
    q.push(20);
    q.push(30);
    assert(q.size() == 3);

    // Test dequeue
    assert(q.front() == 10);
    q.pop();
    assert(q.front() == 20);
    q.pop();
    assert(q.size() == 1);

    // Test clear
    while (!q.empty())
    {
        q.pop();
    }
    assert(q.size() == 0);

    // Test exception handling
    try
    {
        if (!q.empty())
        {
            int frontValue = q.front(); // Use the return value
            std::cout << "Front value: " << frontValue << std::endl;
        }
    }
    catch (const std::exception &e)
    {
        std::cout << "Caught exception: " << e.what() << std::endl;
    }

    // Test move semantics
    q.push(40);
    q.push(50);
    std::queue<int> q2 = std::move(q);
    assert(q2.size() == 2);
    assert(q.empty()); // Original queue should be empty after move

    assert(q2.front() == 40);
    q2.pop();
    assert(q2.front() == 50);
    q2.pop();

    std::cout << "All tests passed!" << std::endl;
    return 0;
}
