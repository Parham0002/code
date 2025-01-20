/*
Make a template print function to print an array.
Make a template function pointer type to point to the print function
Call the print function using an instance of the function pointer type to print an example array of type int.*/
#include "ex26.h"

// Template function to print an array
template <typename T>
void printArray(const std::vector<T> &arr)
{
    assert(!arr.empty() && "Array must not be empty!");

    for (const auto &element : arr)
    {
        std::cout << element << " ";
    }
    std::cout << std::endl;
}
// Template alias for a function pointer type
template <typename T>
using PrintFunctionPointer = void (*)(const std::vector<T> &);

// instantiations for required types
template void printArray<int>(const std::vector<int> &);
template void printArray<float>(const std::vector<float> &);
template void printArray<double>(const std::vector<double> &);
template void printArray<std::string>(const std::vector<std::string> &);
