#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){

unsigned int rndomnum, guess ;
int result; 
int max_att = 10;
int attempts = 0;
char play_again;

do{
    attempts = 0;    
    srand(time(0));
    rndomnum = rand() % 100;
    
printf("I have chosed the number now guess the number between 0 and 99 and try to beat me. you have %d tries.\n", max_att);

while (attempts < max_att){
    printf("enter your guess:");
    result = scanf("%u", &guess);

    if(result != 1){
        printf("only number! please try again between 0 and 99\n");
        while (getchar() != '\n');
        continue;
    }
    if (guess > 99){
        printf("please chose only number and only between 0 and 99.\n");
        continue;
    }
    attempts++;
    if (guess > rndomnum){
        printf("to high try lower number.\n\n");
    } else if (guess < rndomnum){
        printf("to low try again but higher.\n\n");
    } else {
        printf("wow you won you beat me :) the number that i had was: %u\n",rndomnum);
        break;
    }

    if (attempts < max_att) {
        printf("come on you got %d attempts still left.\n\n", max_att - attempts);
    } else {
        printf("nice try buddy you are out of attemps. the number i had was : %u\n",rndomnum);
    }
}
    printf ("do you want to play again (y/n)?");
  while (getchar() != '\n'); 
        scanf("%c", &play_again);

    } while (play_again == 'y' || play_again == 'Y');  

    printf("OK, thanks ! bye!\n");
    return 0;

}
