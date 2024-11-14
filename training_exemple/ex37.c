#include <stdio.h>
#include <string.h>

#define LEN 50

static char *split_str(char *str, char delim);

int main()
{
    char string[LEN];
    char delim = ',';

    printf("write a few car brand and use comma between:");
    fgets(string, sizeof(string), stdin);

    string[strcspn(string, "\n")] = '\0';

    char *token = split_str(string, delim);
    while (token != NULL)
    {
        printf("%s\n", token);
        token = split_str(NULL, delim);
    }

    return 0;
}

static char *split_str(char *str, char delim)
{
    static char *current_pos = NULL;

    if (str != NULL)
    {
        current_pos = str;
    }

    if (current_pos == NULL || *current_pos == '\0')
    {

        return NULL;
    }

    char *start = current_pos;

    while (*current_pos != '\0' && *current_pos != delim)
    {
        current_pos++;
    }

    if (*current_pos == delim)
    {
        *current_pos = '\0';
        current_pos++;
    }

    return start;
}
