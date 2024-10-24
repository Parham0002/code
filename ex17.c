#include <stdio.h>
#include <string.h>

#define size 20 

int main(){

char charac [size];

    printf("enter a string:\n");
    scanf("%s", charac);

    int len = strlen(charac);

    printf("reversed string: ");

for (int i = len - 1; i >= 0; i--)
{
   printf("%c", charac[i]);
}
printf("\n");
    return 0;
}