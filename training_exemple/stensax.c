
#include <stdio.h>

int main(){

int player1;
int player2;
char playagain;

do {
    while(1) {
printf("weolcome to sten sax påse\n");
printf("1 = sten ,2 = sax ,3 = påse\n");

printf("player1 enter your choice (1,2,3)\n");
if(scanf("%d", &player1) != 1 || player1 < 1 || player1 > 3) {

    while(getchar() != '\n');
    printf("wrong input please enter 1,2,3.\n");
} else {
    break;
} 
}

while(1){
printf("player2 enter your choice (1,2,3)\n");
if(scanf("%d", &player2) != 1 || player2 < 1 || player2 > 3){

    while(getchar() != '\n');
    printf("wrong input please enter 1,2,3.\n");
} else {
    break;
}
} 

if (player1 == player2)
{
    printf("it is a draw");
} 
else if ((player1 == 1 && player2 == 2) ||  (player1 == 2 && player2 == 3) ||  (player1 == 3 && player2 == 1)) {
    printf ("player 1 wins.\n");  
} else {
printf("player 2 wins.\n");

}
printf("do you want to play again ?(y/n)");
while (getchar() != '\n');
scanf("%c", &playagain);

while (getchar() != '\n');
}
while (playagain == 'y' || playagain == 'Y');

 printf("OK, thanks ! bye!\n");
    return 0;
} 