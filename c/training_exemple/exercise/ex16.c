/**
 * @file ex16.c
 * @author Parham Rezaei (knightpslow@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-10-22
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <stdio.h>
#include <string.h>

#define arr 10

int main(void){
unsigned int num[arr]= {1, 3, 4, 8, 2, 7, 6, 9, 5, 0};
printf("The array filled with random numbers:\n");

for (size_t i = 0; i < 10; i++)
{

    printf("%u ", num[i]);
}
printf("\n");
for (unsigned int i = 0; i < arr; ++i)
{
    for (unsigned int k = i +1; k < arr; ++k)
    {

    int tmp;

    if (num[i] > num[k])
    {
           int tmp = num[i];
            num[i] = num[k];
            num[k] = tmp;
    }
    
    }
}
for (size_t i = 0; i < 10; i++)
{
   
    printf("%u ", num[i]);
}
printf("\n");

return 0;
}