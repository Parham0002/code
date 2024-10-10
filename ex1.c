#include <stdio.h>

/// @brief macro for the "hello world" string
#define a "hello world"

/** 
 * @brief the main function of the program
 * 
 * this function prints the string defined by macro `a` to the console.
 * 
 * @return int returns 0 means successful execution.
 */

int main(){
   printf("%s\n", a);
   return 0;
}