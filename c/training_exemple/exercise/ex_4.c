/**
 * @file ex_4.c
 * @author Parham Rezaei (knightpslow@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-10-21
 * 
 * @copyright Copyright (c) 2024
 * 
 */
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