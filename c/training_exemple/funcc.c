/**
 * @file func.c
 * @author Parham Rezaei (knightpslow@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-10-29
 * 
 * @copyright Copyright (c) 2024
 * 
 */

/*#include <stdio.h>

int func(int x, int y, int z);

int main()
{
    int num =0;
    int num1=0;
    int num2=0;

 (void)printf("what is your 3 numbers you want to get the average for?\n");

 (void)scanf("%d %d %d",&num,&num1,&num2);

 // printf("%d,%d,%d",num,num1,num2);

 (void)printf("average is : %d \n", func(1,2,3));


 return 0;
}

int func(int x, int y, int z)
{
    int average = (x + y + z) / 3;

    return average;
}*/

/*#include <stdio.h>

int func(int x);

int main()
{
    int num = 0;
   
    (void)printf("what number you want to know if its prime or not?\n");

    (void)scanf("%d", &num);
    
     func(num);

    // (void)printf("%d is a prime number\n", func(num));

    return 0;
}

int func(int x){
    int prime = 1;

    for (int i = 2; i <= x / 2; i++)
    {
        if (x % i == 0)
        {
            prime = 0;
            
            (void)printf("is not a prime number\n");
            break;
        } 
        }
        if (prime)
        {
           (void)printf(" is a prime number\n");
        }

        return prime;
        }*/

#include <stdio.h>

void func(char str[]);

int main()
{
    char carh[20];

    (void)printf("what is your string?\n");

    (void)scanf("%s", carh);

    func(carh);

    return 0;
}

void func(char str[])
{
    for (int i = 0; i < 20; i++)
    
    {
       printf("%s", str);
    }
    

}