#include <stdio.h>


int main(){
int matrix[3][3];

printf("enter all the elements for 3x3 array:\n");
for (int i = 0; i < 3 ; i++){
    for (int k = 0; k < 3; k++){

printf("Enter value for arr[%d][%d]: ", i, k);
scanf("%d", &matrix[i][k]);
}    
}
printf("\nthe 3x3 array is:\n");
for (int i = 0; i < 3 ; i++)
{
  for (int k = 0; k < 3; k++)
  {
    printf("%d ", matrix[i][k]);
  }
  printf("\n");
}
  return 0;
    
    
}