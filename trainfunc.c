/*#include <stdio.h>


int length (const char *str);

void swap(int *a , int *b);

int main(){

char str[256];

int a;

int b;

int (*lengthptr)(const char *) = length;

(void)printf("enter the string:");

(void)scanf("%s", str);

int lenghtt = lengthptr(str);

(void)printf("the lenght of string is: %d\n", lenghtt);

(void)printf("enter two integer for a and b:");

(void)scanf("%d %d", &a, &b);

(void)printf("before swaped your numbers are a = %d ,b = %d\n", a, b);

swap(&a , &b);

(void)printf("the swaped number are a = %d ,b = %d\n", a, b);

    return 0;
}
int length(const char *str){

    int len = 0;
    while (*str != '\0')
    {
        len++;
        str++;
    }
    return len;
}

void swap(int *a, int *b){

    int temp = *a;
    *a = *b;
    *b = *a;

}*/

#include <stdio.h>

#define LEN 10

void arra(int *arr, int size);

int main()
{

    int arr[LEN] = {1, 3, 4, 7, 6, 0, 9, 8, 5, 2};

    int size = LEN;

    void (*arraptr)(int *, int) = arra;

    printf("write a array of %d:\n", size);

    for (int i = 0; i < size; i++)
    {
        
        (void)scanf("%d", &arr[i]);
    }

    arraptr(arr, size);

    return 0;
}
void arra(int *arr, int size)
{

    int temp;

    for (int i = 0; i < size - 1; i++)
    {
        for (int j = 0; j < size - 1; j++)
        {

            if (arr[j] > arr[j + 1])
            {

                temp = arr[j];

                arr[j] = arr[j + 1];

                arr[j + 1] = temp;
            }
        }
    }

    printf("The sorted array in ascending order is:\n");
    for (int i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }

    printf("\n");
}
