#include <stdio.h>

#define LEN 5
#define LENN 10

void arrone(int *arr, int size);

void arrtwo(int *arr, int size);



int main(){

int arro[LEN] = {3, 0, 2, 1, 4};

int arrt[LEN] = {7, 6, 8, 9, 5};

int *arroptr = arro;
int *arrtptr = arrt;

int arrthre[LENN] ;

int size = LEN;




arrone(arro, LEN);

arrone(arrt, LEN);

arrone(arrthre,LENN);



    return 0;
}
void arrone(int *arr, int size){

 int temp;

 for (int i = 0; i < size -1; i++)
 {
    for (int j = 0; j < size -1; j++)
    {
        if (arr[j] > arr[j + 1])
        {
           temp = arr[j];
           arr[j] = arr[j + 1];
           arr[j + 1] = temp;
        }
        
    }
    
 }

 printf("The FIRST sorted array in ascending order is:\n");
 for (int i = 0; i < size; i++)
 {
    printf("%d ", arr[i]);
 }
 (void)printf("\n");
}
