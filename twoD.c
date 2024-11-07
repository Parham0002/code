#include <stdio.h>

#define SIZE 3



void multiply_constant(int matrix[SIZE][SIZE], int constant);

void add_constant(int matrix[SIZE][SIZE], int constant);

void display_matrix (int matrix[SIZE][SIZE]);

void transpose_matrix(int matrix[SIZE][SIZE]);

int main(){


int matrix[SIZE][SIZE] = {{3,56,67} , {36,89,79} , {0,76,45}};

int constant;

int choices;

char onemore;


void (*mptr[])(int [SIZE][SIZE]) = {display_matrix,transpose_matrix};

void (*mptr_2[])(int [SIZE][SIZE],int) = {add_constant,multiply_constant};

// void (*matrixptr)(int [SIZE][SIZE]) = display_matrix;

// void (*multiptr)(int [SIZE][SIZE] , int ) = multiply_constant;

// void (*addiptr)(int [SIZE][SIZE] , int ) = add_constant;

// void (*transptr)(int [SIZE][SIZE] ) = transpose_matrix;


do {
    printf("Chose from the list below:\n");

    printf("1. Display orginal matrix:\n");

    printf("2. Multiply matrix by constant:\n");

    printf("3. Add constant to matrix:\n");

    printf("4. Transpose matrix:\n");

    printf("5. Exit\n");


    printf("Enter your choice:\n");

    scanf("%d" , &choices);

    switch (choices)
    {
        case 1:

               matrixptr(matrix);
                break;

        case 2:
                printf("Enter the constant you want to multiply: ");

                scanf("%d", &constant);

                multiptr(matrix, constant);

                matrixptr(matrix);  
                break;

        case 3:
               printf("Enter the constant you want to add: ");

                scanf("%d", &constant);

                addiptr(matrix, constant);

                matrixptr(matrix);  
                break;

        case 4:

                transptr(matrix);

                matrixptr(matrix);
                break;

        case 5:

                printf("Exiting program.\n");
                
                return 0;
    default:
            printf("Invalid choice! Please try again.\n");

            break;
    }

    printf("do you want to do another one?(y/n)");

    getchar(); 

    scanf("%c", &onemore);

    printf("\n");

}

while (onemore == 'y' || onemore == 'Y');

    return 0;
}


void display_matrix (int matrix[SIZE][SIZE]){

for (int i = 0; i < SIZE; i++)
{
    for (int j = 0; j < SIZE; j++)
    {
        (void)printf("%d ", matrix[i][j]);
    }

    (void)printf("\n");
}

} 

void multiply_constant(int matrix[SIZE][SIZE], int constant){

for (int i = 0; i < SIZE; i++)
{
    for (int j = 0; j < SIZE; j++)
    {
         matrix[i][j] *= constant;
    }
}
}

void add_constant(int matrix[SIZE][SIZE], int constant){

for (int i = 0; i < SIZE; i++)
{
    for (int j = 0; j < SIZE; j++)
    {
         matrix[i][j] += constant;
    }  
    
    }
}

void transpose_matrix(int matrix[SIZE][SIZE]){

for (int i = 0; i < SIZE; i++)
{
    for (int j = i + 1; j < SIZE; j++)
    {
        int temp = matrix[i][j];
        matrix[i][j] = matrix[j][i];
        matrix[j][i] = temp; 
    }  
}
}
