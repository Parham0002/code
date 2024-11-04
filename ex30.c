#include <stdio.h>


void add_5(int *num);

void say_value(int a);

int main(){

void (*funcptr)(int) = say_value;

int a = 5;

char b ='s';

(void)printf("orginal value of a: %d\n", a);

(void)printf("orginal value of b: %c\n", b);


int *pa = &a;

char *pb = &b;

*pa = 12;

*pb= 'd';
    
    (void)printf("Modified value of a: %d\n", *pa);

    (void)printf("Modified value of b: %c\n", *pb);

    add_5(&a); 

    (void)printf("New value after adding 5: %d\n", a);

    funcptr(a);


 return 0;
}
void add_5(int *num){

    *num += 5;

} 
void say_value(int a){

    printf("Value of a is %d\n", a);

}