#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void randomm (int *arr , int size);

void print (int *arr , int size);

void twodarr (int rows, int cols, int arr[rows][cols]);


int main(){

void (*randomptr)(int *, int) = randomm;

void (*printptr)(int *, int) = print;

void (*twodarrptr)(int ,int , int[][3]) = twodarr;

int rows = 2;

int cols = 3;

int arr2[2][3];

int arr[10];

int size = sizeof(arr) / sizeof(arr[0]);

srand(time(NULL));

randomptr(arr, size);

printptr(arr, size);

twodarrptr(rows, cols, arr2);

    return 0;
}


void randomm (int *arr , int size){

for (int i = 0; i < size ; i++)
{
    arr[i] = rand() % 100;
}


}
void print (int *arr , int size){

printf("Array filled with random numbers:\n");

for (int i = 0; i < size; i++) {
    printf("%d ", arr[i]);
    }
    printf("\n");
}

void twodarr (int rows, int cols, int arr[rows][cols]){

(void)printf("2d array:\n");

for (int i = 0; i < rows; i++)
{
    for (int j = 0; j < cols; j++)
    {
        arr[i][j] = rand() % 100;

       (void)printf("%d ", arr[i][j]);
    }
    (void)printf("\n");
}
(void)printf("\n");

}