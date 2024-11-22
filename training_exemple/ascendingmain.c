#include <stdio.h>
#include <assert.h>
#include "ascending.h"
#define LEN 5

void printArray(int *arr, int size);

void runtest1();
void runtest2();
void runtest3();
void runtest4();

int main()
{

    runtest1();
    runtest2();
    runtest3();
    runtest4();

    printf("All tests passed successfully!\n");

    return 0;
}
void printArray(int *arr, int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}
void runtest1()
{
    int arr1[LEN] = {5, 2, 9, 1, 5};
    int size1 = sizeof(arr1) / sizeof(arr1[0]);

    assert(checksorted(arr1, size1) == false);

    array(arr1, size1);

    assert(checksorted(arr1, size1) == true);

    printf("Test Case 1 Passed: ");
    printArray(arr1, size1);
}
void runtest2()
{
    int arr2[LEN] = {1, 2, 3, 4, 5};
    int size2 = sizeof(arr2) / sizeof(arr2[0]);

    assert(checksorted(arr2, size2) == true);

    array(arr2, size2);

    assert(checksorted(arr2, size2) == true);

    printf("Test Case 2 Passed: ");
    printArray(arr2, size2);
}
void runtest3()
{
    int arr3[LEN] = {3, 3, 3, 3, 3};
    int size3 = sizeof(arr3) / sizeof(arr3[0]);

    assert(checksorted(arr3, size3) == true);

    array(arr3, size3);

    assert(checksorted(arr3, size3) == true);

    printf("Test Case 3 Passed: ");
    printArray(arr3, size3);
}
void runtest4()
{
    int arr4[LEN] = {5, 4, 3, 2, 1};
    int size4 = sizeof(arr4) / sizeof(arr4[0]);

    assert(checksorted(arr4, size4) == false);

    array(arr4, size4);

    assert(checksorted(arr4, size4) == true);

    printf("Test Case 4 Passed: ");
    printArray(arr4, size4);
}
