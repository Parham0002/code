#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void func (int arr[], int size);

void printfunc(int arr[], int size);

int main(){
int arr[10];
int size = 10;

srand(time(NULL));

func(arr, size);

printfunc(arr, size);
    return 0;
}

void func (int arr[], int size){

int arrayy[10];

for (int i = 0; i < 10; i++)
{
     arr[i] = rand() % 99 + 1;
   
   for (int j = 0; j < i; j++)
   {
    if (arr[j] == arr[i])
    {
        arr[i] = rand() % 99 + 1;
       j = -1;
    }
    
   }
 } 
}

void printfunc(int arr[], int size){

(void) printf("An array filled with random numbers: ");

   for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }

printf("\n");
}