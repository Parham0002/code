#include <stdio.h>

int main(){

int allnum;
unsigned int num;
int result;
unsigned int sum = 0;
char try_again;
int zero = 0;

do {
    sum = zero;
while(1){
printf("write your positiv number for the sum:");
result = scanf("%d", &allnum);

 if (result != 1)
 {
    while (getchar() != '\n');
    printf("only unsigned number! try again\n");
    continue;
 }

 if (allnum < 0){
    printf("only unsigned number! try again\n");
    continue;;
 }

num = (unsigned int)allnum;
break;

}

for (int i = 0; i <= num; i += 2)
{
    sum += i;
}
printf("this is sum of your even number up to %u: %u\n", num, sum);

printf("do you want to try again with diffrent number?(y/n)");

while (getchar() != '\n');
scanf("%c", &try_again);

while (getchar() != '\n');
}
while (try_again == 'y' || try_again == 'Y');

 printf("OK, thanks ! bye!\n");
    return 0;
}