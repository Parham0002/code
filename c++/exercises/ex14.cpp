/*
1) Make a function to fill an array of type int with random numbers int the range 0 and 99.
2) Make a function to print an array of type int to the output.
3) Make a function to swap values of two int variables.
4) Make a function to sort an array of type int. The function shall accept a function pointer of type compare_t to compare two values

    using compare_t = bool (*)(int, int);

void sort_array(size_t length, int *arr, compare_t compare);
    a) When you sort the array, the compare function shall be used to compare the elements

    b) To swap the elements, the swap function of step 3 shall be used.

    c) Implement two functions, compare_asc and compare_desc, to sort the array ascending and descending

bool compare_asc(int a, int b); and bool compare_desc(int a, int b);

    d) You shall be able to sort the array ascending and descending by calling sort_array with different compare functions
    * To handle the arrays use only pointers
 */
#include <iostream>
#include <ctime>
#include <cstdlib>

constexpr int LEN = 5;

using compare_t = bool (*)(int, int);

void ranarr(int *arr, size_t LEN)
{
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    for (int i = 0; i < LEN; i++)
    {
        *(arr + i) = std::rand() % 100;
    }
    std::cout << std::endl;
}
void printarr(int *arr, size_t LEN)
{
    for (int i = 0; i < LEN; i++)
    {
        std::cout << *(arr + i) << " ";
    }
    std::cout << std::endl;
}

void swapvalue(int &one, int &two)
{
    // std::cout << "before swap " << one << " " << two << std::endl;
    int temp = one;
    one = two;
    two = temp;
    // std::cout << "after swap " << one << " " << two << std::endl;
}

void sortarr(size_t LEN, int *arr, compare_t compare)
{
    for (size_t i = 0; i < LEN - 1; ++i)
    {
        for (size_t j = 0; j < LEN - i - 1; ++j)
        {
            if (!compare(*(arr + j), *(arr + j + 1)))
            {
                swapvalue(*(arr + j), *(arr + j + 1));
            }
        }
    }
}

bool compare_asc(int a, int b)
{
    return a < b;
}

bool compare_desc(int a, int b)
{
    return a > b;
}

int main()
{
    int arr[LEN];
    int one = 5;
    int two = 10;
    swapvalue(one, two);

    ranarr(arr, LEN);
    std::cout << "Original array: ";
    printarr(arr, LEN);

    sortarr(LEN, arr, compare_asc);
    std::cout << "Array sorted in ascending order: ";
    printarr(arr, LEN);

    ranarr(arr, LEN);
    std::cout << "New array: ";
    printarr(arr, LEN);

    sortarr(LEN, arr, compare_desc);
    std::cout << "Array sorted in descending order: ";
    printarr(arr, LEN);

    return 0;
}