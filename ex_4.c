#include <stdio.h>
#define NUMBER 8
#ifndef NUMBER
  #error "NUMBER is not define"
#endif

#if NUMBER != 8 && NUMBER != 16 
  #error "NUMBER MUST BE 8 OR 16."
#endif

int main(){

printf("the value of number is: %d\n", NUMBER);

return 0;

}