#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <iterator>
#include <cmath>

// func to check if a number is prime
bool isPrime(int n)
{
    if (n <= 1)
        return false;
    for (int i = 2; i <= std::sqrt(n); ++i)
    {
        if (n % i == 0)
            return false;
    }
    return true;
}
int main()
{
    std::vector<int> numbers;
    std::random_device rd;                            // seed for random number generator
    std::mt19937 gen(rd());                           // mersenne twister random number generator
    std::uniform_int_distribution<> dis(100, 100000); // random numbers between 100 and 100000

    // generate and store 1000 random numbers in the vector
    for (int i = 0; i < 1000; ++i)
    {
        numbers.push_back(dis(gen));
    }

    // remove non prime numbers from vector
    numbers.erase(std::remove_if(numbers.begin(), numbers.end(), [](int n)
                                 { return !isPrime(n); }),
                  numbers.end());

    // sort the vector in ascending order
    std::sort(numbers.begin(), numbers.end());

    // print the elements of the vector using an iterator
    for (auto it = numbers.begin(); it != numbers.end(); ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}