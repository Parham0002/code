/*#include <stdio.h>

void func(int age , float height,char name [16]);


int main(){
int age;

float height;

char name [16];

func(age, height, name);


    return 0;
}

void func(int age , float height,char name [16]){

typedef struct {


    int age;

    float height;

    char name[16];

} person_t;

(void)printf("what is member age , height and name?" );

(void)scanf("%d %f %15s",&age,&height, name);

(void)printf("member age is : %d , height is : %.2f and name is : %s " , age , height , name );

(void)printf("\n");

}
*/
#include <stdio.h>

typedef struct {
    int age;
    float height;
    char name[16];
} person_t;

void func(person_t *p);

int main() {
    person_t person;

    func(&person);

    (void)printf("Member age, height, and name is: %d %.2f %s\n", person.age, person.height, person.name);

    return 0;
} 

void func(person_t *p) {
    (void)printf("What is the member's age, height, and name? ");
    
    (void)scanf("%d %f %15s", &p->age, &p->height, p->name);  
}