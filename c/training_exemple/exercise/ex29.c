#include <stdio.h>



void findprime(unsigned int m, unsigned int n);

int main(){

unsigned int m;

unsigned int n;

(void)printf("write 2 number for get all the prime in that range (m and n)?\n");

if (scanf("%u %u", &m , &n) != 2 || m == n )
{
    printf("Error: Invalid input. Please chose and enter between two positive integers.\n");
        return 1;
}
 

findprime(m, n);

    return 0;
}

void findprime(unsigned int m, unsigned int n){

for (unsigned int num = m; num <= n; num++)
{
    if (num < 2) continue;
    
    int prime = 1;
    
    for (unsigned int i = 2; i * i <= num; i++)
    {
       if (num % i == 0)
       {
       prime = 0;
       break;
       }
       
    }
    if (prime)
    {
        printf("%u is a prime number.\n", num);
    }
    
}

}

