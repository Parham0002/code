#include <stdio.h>
#include<stdlib.h>
#include <time.h>
int main(){

int matrix[2][3];
int (*pmatrix)[3] = matrix;

srand(time(NULL));

for (int i = 0; i < 2; i++){

    for (int j = 0; j < 3; j++){

  *(*(pmatrix + i) + j) = rand() % 100;
}
}

printf("array elements are:\n");

for (int i = 0; i < 2; i++){
    
    for (int j = 0; j < 3; j++){

printf("%d ",*(*(pmatrix + i) + j) );
}
printf("\n");
}



    return 0; 
}