#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "record.txt"
#define NAME_LEN 50

typedef struct
{
    char name[50];
    int id;
} Record;

// Function prototypes with filled-in parameters
void create_record(const char *filename);
void read_records(const char *filename);
void update_record(const char *filename, int id, const char *new_name);
void delete_record(const char *filename, int id);

int main()
{
    int choice;
    char name[NAME_LEN];
    int id;

    do
    {
        printf("\n--- Menu ---\n");
        printf("1. Create Record\n");
        printf("2. Read Records\n");
        printf("3. Update Record\n");
        printf("4. Delete Record\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            create_record(FILENAME);
            break;
        case 2:
            read_records(FILENAME);
            break;
        case 3:
            printf("Enter ID of the record to update: ");
            scanf("%d", &id);
            printf("Enter new Name: ");
            scanf("%s", name);
            update_record(FILENAME, id, name);
            break;
        case 4:
            printf("Enter ID of the record to delete: ");
            scanf("%d", &id);
            delete_record(FILENAME, id);
            break;
        case 5:
            printf("Exiting program.\n");
            break;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 5);

    return 0;
}

// Create a record by accepting user input
void create_record(const char *filename)
{
    FILE *file = fopen(filename, "a");
    if (!file)
    {
        perror("Unable to open file");
        return;
    }

    Record record;
    printf("Enter ID: ");
    scanf("%d", &record.id);
    printf("Enter Name: ");
    scanf("%s", record.name);

    fprintf(file, "%d %s\n", record.id, record.name);
    fclose(file);
    printf("Record created successfully.\n");
}

// Read and display all records from the file
void read_records(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        perror("Unable to open file");
        return;
    }

    Record record;

    printf("ID\tName\n");
    printf("------------------\n");

    while (fscanf(file, "%d %s", &record.id, record.name) != EOF)
    {
        printf("%d\t%s\n", record.id, record.name);
    }
    fclose(file);
}

// Update a record identified by its ID
void update_record(const char *filename, int id, const char *new_name)
{
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        perror("Unable to open file");
        return;
    }

    FILE *tempFile = fopen("temp.txt", "w");
    if (!tempFile)
    {
        perror("Unable to open temporary file");
        fclose(file);
        return;
    }

    int found = 0;
    Record record;

    while (fscanf(file, "%d %s", &record.id, record.name) != EOF)
    {
        if (record.id == id)
        {
            found = 1;
            strcpy(record.name, new_name);
        }
        fprintf(tempFile, "%d %s\n", record.id, record.name);
    }

    fclose(file);
    fclose(tempFile);

    if (found)
    {
        remove(filename);
        rename("temp.txt", filename);
        printf("Record updated successfully.\n");
    }
    else
    {
        printf("Record not found.\n");
        remove("temp.txt");
    }
}

// Delete a record identified by its ID
void delete_record(const char *filename, int id)
{
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        perror("Unable to open file");
        return;
    }

    FILE *tempFile = fopen("temp.txt", "w");
    if (!tempFile)
    {
        perror("Unable to open temporary file");
        fclose(file);
        return;
    }

    int found = 0;
    Record record;

    while (fscanf(file, "%d %s", &record.id, record.name) != EOF)
    {
        if (record.id == id)
        {
            found = 1;
            continue;
        }
        fprintf(tempFile, "%d %s\n", record.id, record.name);
    }

    fclose(file);
    fclose(tempFile);

    if (found)
    {
        remove(filename);
        rename("temp.txt", filename);
        printf("Record deleted successfully.\n");
    }
    else
    {
        printf("Record not found.\n");
        remove("temp.txt");
    }
}
