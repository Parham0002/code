#include <stdio.h>


// 0100 0000
// 1

void decimal2binary(int a);

int main(){

int a;

(void)printf("write a decimal number: ");

(void)scanf("%d", &a);

if (a < 0 || a > 255)
{
    printf("Please enter a number between 0 and 255.\n");

    return 1;
}

(void)printf("the 8-bit binary of %d is : ", a);

decimal2binary(a);

return 0;
}

void decimal2binary(int a){

for (int i = 7; i >= 0; i--)
{
    int bit = (a >> i) & 1;

    (void)printf("%d", bit);
}
(void)printf("\n");
}