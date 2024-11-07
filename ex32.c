#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define LEN 5

typedef bool (*compare_t)(int, int);

void randommm(int *arr, int size);

void printarr(int *arr, int size);

void swapp (int *x, int *y);

void sort_array(int *arr, int size, compare_t compare);

bool compare_asc(int a, int b);

bool compare_desc(int a, int b);

int main()
{

    int arr[LEN];

    int size = LEN;

    int x = 5;

    int y = 6;

    void (*rndmptr[2])(int *, int) = {randommm, printarr};

    void (*swappptr)(int * , int *) = swapp;

    void (*sort_arrayptr)(int *, int , compare_t compare) = sort_array;

    bool (*compare_asc_descptr[])(int , int ) = {compare_asc, compare_desc};

    srand(time(NULL));

    printf("Array filled with random numbers:\n");

    rndmptr[0](arr, size);

    rndmptr[1](arr, size);

    printf("number before swap: %d %d\n", x , y);

    swappptr(&x, &y);

    printf("number after swap: %d %d\n", x, y);

    printf("Array sorted in ascending order:\n");

    sort_arrayptr(arr, LEN, compare_asc_descptr[0]);

    rndmptr[1](arr, size);

    printf("Array sorted in descending order:\n");

    sort_arrayptr(arr, LEN, compare_asc_descptr[1]);

    rndmptr[1](arr, size);

    return 0;
}

void randommm(int *arr, int size){

    for (int i = 0; i < size; i++)
    {
        arr[i] = rand () % 100;
    }

}
void printarr(int *arr, int size)
{

    for (int i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void swapp(int *x, int *y) {

   int temp = *x;
   *x = *y;
   *y = temp;
}

void sort_array(int *arr, int size, compare_t compare)
{
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = 0; j < size - 1 - i; j++)
        {
        
            if (compare(arr[j], arr[j + 1]))
            {
                swapp(&arr[j], &arr[j + 1]);
            }
        }
    }
}

bool compare_asc(int a, int b)
{
    return a > b; 
}

bool compare_desc(int a, int b)
{
    return a < b;
}