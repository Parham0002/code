#include <stdio.h>

#include <stdint.h>

#include <stdlib.h>

typedef struct

{

    char *name;

    uint8_t age;

} person_t;

int main(void)
{
    int person_count;
    printf("Enter the number of persons: ");
    scanf("%d", &person_count);

    person_t *person_array = malloc(sizeof(person_t) * person_count);

    if (person_array == NULL)
    {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    for (int i = 0; i < person_count; i++)
    {
        person_array[i].name = malloc(100 * sizeof(char));
        if (person_array[i].name == NULL)
        {
            printf("Memory allocation failed.\n");
            exit(1);
        }

        printf("Enter the name of person %d: ", i + 1);
        scanf("%s", person_array[i].name);
        printf("Enter the age of person %d:", i + 1);
        scanf("%hhd", &person_array[i].age);
    }

    printf("Person details:\n");
    for (int i = 0; i < person_count; i++)
    {
        printf("Name: %s, Age: %d\n", person_array[i].name, person_array[i].age);
    }

    for (int i = 0; i < person_count; i++)
    {
        free(person_array[i].name);
    }
    free(person_array);

    return 0;
}
