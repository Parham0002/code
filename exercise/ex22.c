#include <stdio.h>
#include <ctype.h>

int main()
{
char str[20];
char *pstr= str;

printf("please write your sentence it can be uppercase or lowercase letter: \n");
scanf("%19s", str);

while (*pstr != '\0')
{
  if (isupper(*pstr))
 {
    *pstr = tolower(*pstr);

 } else if (islower(*pstr)) 
 {
    *pstr = toupper(*pstr);
}
pstr++;
 
}
printf("converted string: %s\n", str);

    return 0;
}