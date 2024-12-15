#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
int num[10];
int (*pnum)[10] = &num;

srand(time(NULL));

for (int i = 0; i < 10; i++)
{
    (*pnum)[i] = rand() % 100;
}


printf("array elements are: ");
for (int i = 0; i < 10; i++)
{
   printf("%d ", (*pnum)[i]);
}

for (int i = 0; i < 10; i++)
{
    for (int j = i + 1; j < 10; j++)
    {
        int tmp;
        if ((*pnum)[i] > (*pnum)[j])
        {
           int tmp = (*pnum)[i];
           (*pnum)[i] = (*pnum)[j];
           (*pnum)[j] = tmp;
        }
        
        
    }
    
}
printf("\n");
printf("Sorted array elements are: ");
for (int i = 0; i < 10; i++)
{
   
    printf("%d ", (*pnum)[i]);
}
printf("\n");
    return 0;
}