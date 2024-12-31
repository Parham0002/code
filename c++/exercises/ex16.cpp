/*Make a function to fill an array of type int with unique random numbers in the range of 1 and 99.

Make another function to print the array to the output.

Example: An array filled with random numbers: {9, 3, 8, 13, 5, 2, 6, 7, 1, 4}*/

#include <iostream>
#include <ctime>

constexpr int SIZE = 10;

void fillarr(int *arr, int SIZE);

void printarr(int *arr, int SIZE);

int main()
{
    int arr[SIZE];
    fillarr(arr, SIZE);
    std::cout << "An array filled with random numbers: {";
    printarr(arr, SIZE);

    return 0;
}

void fillarr(int *arr, int SIZE)
{
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    for (int i = 0; i < SIZE; i++)
    {
        *(arr + i) = std::rand() % 99 + 1;
    }
    std::cout << std::endl;
}

void printarr(int *arr, int SIZE)
{
    for (int i = 0; i < SIZE; i++)
    {
        std::cout << *(arr + i);
        if (i < SIZE - 1)
        {
            std::cout << ",";
        }
    }
    std::cout << "}" << std::endl;
}