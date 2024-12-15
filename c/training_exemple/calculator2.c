#include <stdio.h>
#include <stdbool.h>

int add(int x , int y);

int sub(int x, int y);

int mul(int x, int y);

int dev(int x, int y);

bool state = true;

int main(){
    int x;
    int y;
    char operator;
    int result;

    (void)printf("enter two numbers:");
    (void)scanf("%d %d", &x, &y);
    (void)printf("enter an operator(+,-,*-/):");
    (void)scanf(" %c", &operator);

 int (*fptr)(int,int);
  
    switch (operator)
    {
    case '+':
        fptr = add;
        break;
    case '-':
        fptr = sub;
        break;
    case '*':
        fptr = mul;
        break;
    case '/':
        if (y == 0)
        {
            (void)printf("You cannot divide by 0\n");
        }
        else
        {
            fptr = dev;
            (void)printf("Result: %d\n", result);
        }
        break;

    default:
    (void)printf("error invalid input!\n");
    
    }
    if (state)
    {
        int result = fptr(x, y);
        (void)printf("Result: %d\n", result);
    }
    
   

    return 0;
}

int add(int x, int y)
{

    return x + y;
}
int sub(int x, int y)
{

    
    return x - y;
}
int mul(int x, int y)
{

    return x * y;
}
int dev(int x, int y)
{

    return x / y;
}