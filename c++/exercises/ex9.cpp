/*Make a program to fill a 10-element int array with random numbers in the range of 0 and 99, then

print the array to the output.
sort the array ascending(from the smallest to the largest) and then
Print the sorted array to the output.
*/

#include <iostream>
#include <ctime>

constexpr int LENGHT = 10;
constexpr int MAX = 99;

int main()
{
    int arr[LENGHT];
    int *parr = nullptr;
    std::srand(std::time(NULL));
    for (parr = arr; (parr - arr) < LENGHT; parr++)
    {
        *parr = std::rand() % (MAX + 1);
    }
    std::cout << "array with filled numbers:";
    for (parr = arr; (parr - arr) < LENGHT - 1; parr++)
    {
        std::cout << *parr << " ";
    }
    std::cout << std::endl;

    for (int *iptr = arr; (iptr - arr) < LENGHT; iptr++)
    {
        for (int *jptr = iptr + 1; (jptr - arr) < LENGHT; jptr++)
        {
            if (*iptr > *jptr)
            {
                int temp = *iptr;
                *iptr = *jptr;
                *jptr = temp;
            }
        }
    }

    std::cout << "The sorted array:";
    for (parr = arr; (parr - arr) < LENGHT - 1; parr++)
    {
        std::cout << *parr << " ";
    }
    std::cout << std::endl;

    return 0;
}