#include <stdio.h>
#include <string.h>

char compare(char *str, char *strr);



int main(){

char str[20];

char strr[20];

char (*compareptr)(char* , char*) = compare;

(void)printf("enter the first string of characters:\n");

(void)scanf("%19s", str);

(void)printf("enter the second string of characters:\n");

(void)scanf("%19s", strr);

int result = compareptr(str, strr);

if (result == 1)
{
    (void)printf("they are equal\n");
} else
{
   (void)printf("they are not equal\n"); 
}



    return 0;
}

char compare(char *str, char *strr){

if (strcmp(str,strr)== 0)
{
    return 1;
} else
{
    return 0;
}

}