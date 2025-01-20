#ifndef EX26_H
#define EX26_H

#include <vector>
#include <iostream>
#include <cassert>

// Template function to print an array
template <typename T>
void printArray(const std::vector<T> &arr);

/*void printArray(const std::vector<T> &arr)
{
    assert(!arr.empty() && "Array must not be empty!");

    for (const auto &element : arr)
    {
        std::cout << element << " ";
    }
    std::cout << std::endl;
}
*/

// Template alias for a function pointer type
template <typename T>
using PrintFunctionPointer = void (*)(const std::vector<T> &);

#endif