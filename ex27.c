/**
 * @file ex27.c
 * @author Parham Rezaei (knightpslow@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-11-01
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <stdio.h>

int funnc(int *arr, int size);

float average(int *arr, int size);

int specific(int *arr, int size, int value);

int main(){

int arrrr[20];

int num;

int value;

int(*funcptr)(int* ,int) = funnc;

float(*averageptr)(int* ,int) = average;

int(*specificptr)(int* ,int ,int) = specific;

(void)printf("enter the number of elements 1 to 20:\n");

(void)scanf("%d", &num);

if (num > 20 || num <= 0)
{
    (void)printf("error invalid number of element.\n");

    return 1;
}

(void)printf("enter an array of numbers:\n");

for (int i = 0; i < num; i++)
{
    (void)printf("Element %d: ", i + 1);

    (void)scanf("%d", &arrrr[i]);
}

int largest = funcptr (arrrr, num);

(void)printf("The largest value is: %d\n", largest);

float averagee = averageptr (arrrr, num);

(void)printf("The average is: %.2f\n", averagee);

(void)printf("Enter the value to find: ");

(void)scanf("%d", &value);

int specific = specificptr (arrrr, num, value);

if (specific != -1)
{
    (void)printf("Value %d found at element: %d\n", value, specific + 1);

} else {

    (void)printf("Value %d not found in the array.\n", value);
}

    return 0;
}


int funnc(int *arr, int size){

int largest = arr[0];

for (int i = 1; i < size; i++)
{
    if (arr[i] > largest)
    {
       largest = arr[i];
    }
    
}
return largest;
}

float average(int *arr, int size){

float sum = 0;

for (int i = 0; i < size; i++)
{
    sum += arr[i];
}
float averagee = sum / size;

return averagee;

}

int specific(int *arr, int size, int value){

for (int i = 0; i < size; i++)
{
   if (arr[i] == value)
   {
    return i;
   }
   return -1;
}

}