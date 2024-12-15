#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "record.bin"
#define NAME_LEN 50

typedef struct
{
    char name[NAME_LEN];
    int id;
} Record;

// Function prototypes
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
    FILE *file = fopen(filename, "ab"); // Append in binary mode
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

    fwrite(&record, sizeof(Record), 1, file); // Write the record to the file
    fclose(file);
    printf("Record created successfully.\n");
}

// Read and display all records from the file
void read_records(const char *filename)
{
    FILE *file = fopen(filename, "rb"); // Read in binary mode
    if (!file)
    {
        perror("Unable to open file");
        return;
    }

    Record record;

    printf("ID\tName\n");
    printf("------------------\n");

    while (fread(&record, sizeof(Record), 1, file) == 1)
    {
        printf("%d\t%s\n", record.id, record.name);
    }
    fclose(file);
}

// Update a record identified by its ID
void update_record(const char *filename, int id, const char *new_name)
{
    FILE *file = fopen(filename, "rb+"); // Read and write in binary mode
    if (!file)
    {
        perror("Unable to open file");
        return;
    }

    Record record;
    int found = 0;

    while (fread(&record, sizeof(Record), 1, file) == 1)
    {
        if (record.id == id)
        {
            found = 1;
            strcpy(record.name, new_name);

            fseek(file, -sizeof(Record), SEEK_CUR); // Move back to overwrite the record
            fwrite(&record, sizeof(Record), 1, file);
            break;
        }
    }

    fclose(file);

    if (found)
    {
        printf("Record updated successfully.\n");
    }
    else
    {
        printf("Record not found.\n");
    }
}

// Delete a record identified by its ID
void delete_record(const char *filename, int id)
{
    FILE *file = fopen(filename, "rb"); // Read in binary mode
    if (!file)
    {
        perror("Unable to open file");
        return;
    }

    FILE *tempFile = fopen("temp.bin", "wb"); // Temporary file to store remaining records
    if (!tempFile)
    {
        perror("Unable to open temporary file");
        fclose(file);
        return;
    }

    Record record;
    int found = 0;

    while (fread(&record, sizeof(Record), 1, file) == 1)
    {
        if (record.id == id)
        {
            found = 1;
            continue; // Skip the record to delete
        }
        fwrite(&record, sizeof(Record), 1, tempFile);
    }

    fclose(file);
    fclose(tempFile);

    if (found)
    {
        remove(filename);
        rename("temp.bin", filename);
        printf("Record deleted successfully.\n");
    }
    else
    {
        printf("Record not found.\n");
        remove("temp.bin");
    }
}
