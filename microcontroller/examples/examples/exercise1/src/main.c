#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_log.h"

#define MAX_LENGTH 20
#define TAG "MAIN"

void reverseanduppercase(char *str)
{
    int len = strlen(str);

    // Reverse the string
    for (int i = 0; i < len / 2; i++)
    {
        char temp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = temp;
    }

    // Convert to uppercase
    for (int i = 0; i < len; i++)
    {
        str[i] = toupper((unsigned char)str[i]);
    }
}

void app_main(void)
{
    char input[MAX_LENGTH + 1]; // +1 for null terminator

    while (1)
    {
        printf("Enter a string (exactly 20 lowercase letters): ");

        if (scanf("%20s", input) != 1)
        {
            printf("Invalid input. Please enter a valid string.\n");
            while (getchar() != '\n')
                ; // Clear input buffer

            // Yield to other tasks
            vTaskDelay(pdMS_TO_TICKS(100));
            continue;
        }

        // Check if input is exactly 20 characters
        if (strlen(input) != MAX_LENGTH)
        {
            printf("Invalid input. Please enter exactly 20 characters.\n");
            vTaskDelay(pdMS_TO_TICKS(100));
            continue;
        }

        // Validate lowercase letters only
        int valid = 1;
        for (int i = 0; i < MAX_LENGTH; i++)
        {
            if (!islower((unsigned char)input[i]))
            {
                valid = 0;
                break;
            }
        }

        if (!valid)
        {
            printf("Invalid input. Please enter only lowercase letters.\n");
            vTaskDelay(pdMS_TO_TICKS(100));
            continue;
        }

        // Process input
        reverseanduppercase(input);
        printf("Reversed and uppercase string: %s\n", input);

        // Use vTaskDelay instead of usleep
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
