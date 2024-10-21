#include <stdio.h>
/*
int main(){
int num;
int prime = 1;

while (1){


 printf("type your number:");
    scanf("%d", &num); 

if (num < 2 || num > 10000)
{
    printf("invalid input choose between 2 and 10000:\n");
    continue;
}

for (int i = 2; i <= num / 2; i++)
{
   if (num % i == 0){
    prime = 0;
    break;
   }
}
if (prime)
{
    printf("%d is a prime number.\n", num);
} else {
    printf("%d its not a prime number.\n", num);
 }
}

    return 0; 
}
*/

int main(){
int num;
int prime = 1;

do {

 printf("type your number:");
    scanf("%d", &num); 

if (num < 2 || num > 10000)
{
    printf("invalid input choose between 2 and 10000:\n");
  }
} while (num < 2 || num > 10000);

for (int i = 2; i <= num / 2; i++)
{
   if (num % i == 0){
    prime = 0;
    break;
   }
}
if (prime)
{
    printf("%d is a prime number.\n", num);
} else {
    printf("%d its not a prime number.\n", num);
 }
    return 0; 
}
