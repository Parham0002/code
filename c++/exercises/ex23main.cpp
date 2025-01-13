#include "ex23.h"
#include <iostream>

int main()
{
    // Create shapes
    Circle circle("Circle", Point(0, 0), 4);
    Square square("Square", 4);

    // Print areas
    printArea(circle);
    printArea(square);

    // Check equality of circles
    Circle circle2("Circle", Point(0, 0), 4);
    std::cout << (circle == circle2) << std::endl; // Output: 1 (true)

    return 0;
}
