#include <stdio.h>
#include <stdlib.h>

int main(){

unsigned int num;
char tryagain;

do{

while(1){
printf("write your number between 0 and 255 so i can generate it to binary:)\n");
scanf("%u",&num);

if (num > 255){

    printf("Only between 0 and 255!\n");
}else {
    break;
}
}
 printf("here is the binary of %u is :",num);
for (int i = 7; i >= 0; i-- ){
    printf("%u", (num >> i) & 1);
    
}
printf("\n");

printf("do you want try another number?(y/n)");
while (getchar() != '\n');
scanf ("%c", &tryagain);
} 
while (tryagain == 'y' || tryagain == 'Y');

printf("thanks have a nice day!\n");
    return 0;
}