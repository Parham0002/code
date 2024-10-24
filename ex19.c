#include <stdio.h>
#include <string.h>

int main(){

/*char str[50];

printf("enter a sentence:");
fgets(str, sizeof(str), stdin);

for (int i = 0; str[i] != '\0'; i++)
{
    if (str[i] != ' ')
    {
        printf("%c", str[i]);
        
    }else if (i > 0 && str[i-1] != ' ') {
        printf("\n");  
    }
}*/

char str[50];
printf("enter a sentence:");

while (scanf("%s", str) == 1){
  printf("%s\n", str);
}
    return 0;
}