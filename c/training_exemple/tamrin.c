
#include "tamrin.h"

void create_record(const char *filename)
{
    FILE *file = fopen(filename, "ab");
    if (!file)
    {
        perror("unnable to open file");
        return;
    }

    Recordd record;

    printf("Enter ID: ");
    scanf("%d", &record.id);
    printf("Enter Name: ");
    scanf("%s", record.name);

    fwrite(&record, sizeof(Recordd), SINGLE_RECORD, file);
    fclose(file);
    printf("Record created successfully.\n");
}

void read_record(const char *filename)
{
    FILE *file = fopen(filename, "rb");
    if (!file)
    {
        perror("unable to open file");
        return;
    }
    Recordd record;

    printf("ID\tName\n");
    printf("------------------\n");

    while (fread(&record, sizeof(Recordd), SINGLE_RECORD, file) == ONE)
    {
        printf("%d\t%s\n", record.id, record.name);
    }
    fclose(file);
}

void update_record(const char *filename, int id, const char *newname)
{
    FILE *file = fopen(filename, "rb+");
    if (!file)
    {
        perror("unable to open file");
        return;
    }
    Recordd record;
    int found = ZERO;
    while (fread(&record, sizeof(Recordd), SINGLE_RECORD, file) == ONE)
    {
        if (record.id == id)
        {
            found = ONE;
            strcpy(record.name, newname);

            fseek(file, -sizeof(Recordd), SEEK_CUR);
            fwrite(&record, sizeof(Recordd), SINGLE_RECORD, file);
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

void delete_record(const char *filename, int id)
{
    FILE *file = fopen(filename, "rb");
    if (!file)
    {
        perror("unable to open file");
        return;
    }

    FILE *tempfile = fopen("temp.bin", "wb");
    if (!tempfile)
    {
        perror("unable to open temporary file");
        fclose(file);
        return;
    }

    Recordd record;

    int found = ZERO;

    while (fread(&record, sizeof(Recordd), SINGLE_RECORD, file) == ONE)
    {
        if (record.id == id)
        {
            found = ONE;
            continue;
        }
        fwrite(&record, sizeof(Recordd), SINGLE_RECORD, tempfile);
    }
    fclose(file);
    fclose(tempfile);

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