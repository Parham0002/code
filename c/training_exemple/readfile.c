#include "readfile.h"

fileee *create_fileee(const char *filename)
{
    FILE *file = fopen("test.txt", "w");

    if (file == NULL)
    {
        printf("Failed to open story.txt\n");
        exit(1);
    }
}

void fileee_message(fileee *fileee, const char *message)
{
    FILE *file = fopen("test.txt", "a");
    if (file == NULL)
    {
        printf("Failed to open story.txt\n");
        exit(1);
    }

    fprintf(file, "This is appended text.\n");
}
void destroy_fileee(fileee *fileee)
{
    if (remove("test.txt") == 0)
    {
        printf("File deleted successfully.\n");
    }
    else
    {
        printf("Error deleting file.\n");
    }
}
