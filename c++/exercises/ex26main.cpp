#include "ex26.h"

int main()
{
    // Define an array of type int
    std::vector<int> intArray = {1, 2, 3, 4, 5};
    std::vector<float> floatarray = {2.3, 3.45, 6.5, 7.56, 1.34};

    // Create a function pointer and point it to the printArray function
    PrintFunctionPointer<int> printFunc = printArray<int>;

    // Call the print function using the function pointer
    printFunc(intArray);

    // Create a function pointer for float array and call it
    PrintFunctionPointer<float> printFloatFunc = printArray<float>;
    printFloatFunc(floatarray);

    // for the assertion test

    /*std::vector<int> emptyIntArray;
     std::vector<float> emptyFloatArray;

     printFunc(emptyIntArray);
     printFloatFunc(emptyFloatArray);*/

    return 0;
}
