#include <stdio.h>
#include <ctype.h>

int main(){
   char ch;
   int state = 0;

   printf("write your full name:");

  while((ch = getchar()) !=  '\n' ){

  if(isalpha(ch)){
    if(!state){
        putchar(toupper(ch));
        state = 1;
    } else {
        putchar(tolower(ch));
    }
    }else if( ch == ' '){
        if(state){
            putchar(' ');
            state = 0;
        }

    }
  }
  printf("\n");

return 0;
  }
