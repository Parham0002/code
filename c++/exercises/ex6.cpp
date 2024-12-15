/*Write a program to make a 2 dimensional(3x3) array of type int.
Then ask the user to enter all the elements and then print the array to the output.
Print the array to the output like a table. For example:

123   234  456

54     678  987

12     987  100
*/

#include <iostream>

int main()
{
    const int rows = 3;
    const int cols = 3;
    int arr[rows][cols];

    std::cout << "enter 9 elements for a 3x3 matirx :" << std::endl;

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            std::cin >> arr[i][j];
                }
    }

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            std::cout << arr[i][j] << "\t";
        }
        std::cout << std::endl;
    }

    return 0;
}