#include <iostream>
#include <ctime>
#include <cstdlib>

constexpr int MAXX = 99;
constexpr int ROWS{2};
constexpr int COLS{3};
int main()
{
    int arr[ROWS][COLS];
    std::srand(std::time(nullptr));

    for (int(*rptr)[COLS] = arr; (rptr - arr) < ROWS; rptr++)
    {
        for (int(*cptr) = *rptr; (cptr - *rptr) < COLS; cptr++)
        {
            *cptr = std::rand() % (MAXX + 1);
        }
    }

    for (int(*rptr)[COLS] = arr; (rptr - arr) < ROWS; rptr++)
    {
        for (int(*cptr) = *rptr; (cptr - *rptr) < COLS; cptr++)
        {
            std::cout << *cptr << "\t";
        }
        std::cout << std::endl;
    }

    return 0;
}