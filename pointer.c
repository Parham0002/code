/**
 * @file pointer.c
 * @author Parham Rezaei (knightpslow@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-10-24
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <stdio.h>
#include <string.h>

int main(){

/*const int num = 10; 
const int *pnum = &num;

printf("value of integer: %d\nthe adress of variable: %p\n value of the pointer: %d\n", num, pnum, *pnum );
*/

/*int num[5]= {10, 20, 30, 40, 50};

// int (*pnum)[5] = &num;
int *pnum = num;

for (int i = 0; i < 5; i++)
{
   printf("%d ", *(pnum + i));

   *(pnum + i) = i + 2;
}
printf("\n");
for (int i = 0; i < 5; i++)
{
    printf("%d ", *(pnum + i));
}
printf("\n");*/

int num = 2;

int *pnum = &num;
int **pnnum = &pnum;
printf("values of firstp: %d\nadress of firstp: %p\nvalues of secondp: %d\nadress of seccond: %p\n", *pnum, &pnum, **pnnum, &pnnum);


/*int *pnum = &num;
int *pnnum = pnum;
printf( "values of firstp: %d\nadress of firstp: %p\nvalues of secondp: %d\nadress of seccond: %p\n",*pnum,pnum,*pnnum,pnnum);*/
return 0;
}