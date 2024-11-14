#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 100

int main() {
    char search_word[50];
    char line[MAX_LINE];
    int line_number = 0;
    int found = 0;

    printf("what word you want to search: ");
    scanf("%s", search_word);

    printf("\n");
    
    FILE *file = fopen("text.txt", "r");
    if (file == NULL) {
        printf("Could not open text.txt\n");
        return 1;
    }

    while (fgets(line, MAX_LINE, file) != NULL) {
        line_number++;
        if (strstr(line, search_word) != NULL) {
            printf("Line %d: %s \n", line_number, line);
            found = 1;
        }
    }

    if (!found) {
        printf("The word '%s' was not found in the file.\n", search_word);
    }

    fclose(file);


    return 0;
}