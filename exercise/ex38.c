/*
Make a C program to define a structure type (user_t)  with name(8 letters) and unique id members. Then

1) Make an array of user_t
2) Make a function to fill users with random names and unique ids started from 1
3) Make a function to print the users to a terminal
4) Make a function to write the users to a binary file
5) Make a function to read the users from the file
6) Make a function to change a user name base on its id in the file
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_USER 5
#define NAME_LEN 8

typedef struct
{
    char name[NAME_LEN + 1];
    int id;
} user_t;

void generate_random_name(char *name);

void fill_users(user_t *users, int num_users);

void print_users(const user_t *users, int num_users);

void write_users_to_file(const char *filename, const user_t *users, int num_users);

void read_users_from_file(const char *filename, user_t *users, int num_users);

void change_user_name_in_file(const char *filename, int id, const char *new_name);

int main()
{
    user_t users[NUM_USER];

    // Fill users with random names and unique ids
    fill_users(users, NUM_USER);

    // Print users to the terminal
    printf("Original Users:\n");
    print_users(users, NUM_USER);

    // Write users to a binary file
    const char *filename = "users.dat";
    write_users_to_file(filename, users, NUM_USER);

    // Read users from the binary file
    user_t loaded_users[NUM_USER];
    read_users_from_file(filename, loaded_users, NUM_USER);

    // Print loaded users to the terminal
    printf("\nLoaded Users from File:\n");
    print_users(loaded_users, NUM_USER);

    // Change a user's name based on their id in the file
    int id_to_change = 3;
    const char *new_name = "NEWNAME";
    change_user_name_in_file(filename, id_to_change, new_name);

    // Read and print users again to see the change
    read_users_from_file(filename, loaded_users, NUM_USER);
    printf("\nUsers after Name Change:\n");
    print_users(loaded_users, NUM_USER);

    return 0;
}
void generate_random_name(char *name)
{
    for (int i = 0; i < NAME_LEN; ++i)
    {
        name[i] = 'A' + rand() % 26;
    }
    name[NAME_LEN] = '\0';
}

void fill_users(user_t *users, int num_users)
{
    for (int i = 0; i < num_users; ++i)
    {
        generate_random_name(users[i].name);
        users[i].id = i + 1;
    }
}

void print_users(const user_t *users, int num_users)
{
    for (int i = 0; i < num_users; ++i)
    {
        printf("ID: %d, Name: %s\n", users[i].id, users[i].name);
    }
}

void write_users_to_file(const char *filename, const user_t *users, int num_users)
{
    FILE *file = fopen(filename, "wb");
    if (!file)
    {
        perror("Failed to open file");
        return;
    }
    fwrite(users, sizeof(user_t), num_users, file);
    fclose(file);
}

void read_users_from_file(const char *filename, user_t *users, int num_users)
{
    FILE *file = fopen(filename, "rb");
    if (!file)
    {
        perror("Failed to open file");
        return;
    }
    fread(users, sizeof(user_t), num_users, file);
    fclose(file);
}

void change_user_name_in_file(const char *filename, int id, const char *new_name)
{
    FILE *file = fopen(filename, "r+b");
    if (!file)
    {
        perror("Failed to open file");
        return;
    }

    user_t user;
    while (fread(&user, sizeof(user_t), 1, file))
    {
        if (user.id == id)
        {
            strncpy(user.name, new_name, NAME_LEN);
            user.name[NAME_LEN] = '\0'; 
            fseek(file, -sizeof(user_t), SEEK_CUR);
            fwrite(&user, sizeof(user_t), 1, file);
        }
    }

    fclose(file);
}