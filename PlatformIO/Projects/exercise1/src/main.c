#include <stdio.h>
#include <ctype.h>
#include <esp_task_wdt.h>

#define STRLEN 20

static size_t get_string(char *string, size_t lenght){
    char chr = 0;
    size_t len = 0;

    while (len < lenght)
    {
        chr = getchar();
        if (chr == '\n')
        {
            break;
        }
        else if ((chr >= 'a') && (chr <= 'z'))
        {
            putchar(chr);
            string[len] = toupper(chr);
            len++;
        }
        else {
            ;
        }
        }
        string[len] = '\0';
        return len;
    
}

void app_main(void){
    ESP_ERROR_CHECK(esp_task_wdt_delete(xTaskGetIdleTaskHandle()));

    char string[STRLEN + 1];

    while (1)
    {
        while (EOF != getchar())
        {
            ;
        }
        printf("Enter a string: ");

        size_t length = get_string(string, STRLEN);

        if (length > 0)
        {
            char temp;
            size_t left = 0, right = length - 1;

            while (left < right)
            {
                temp = string[left];
                string[left] = string[right];
                string[right] = temp;
                right--;
                left++;
            }
            printf("\nReverse string: %s\n", string);
        }
        }
    

}
