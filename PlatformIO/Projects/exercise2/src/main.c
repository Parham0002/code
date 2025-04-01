#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <sys/time.h>
#include <ctype.h>
#include "esp_sntp.h"
#include "esp_task_wdt.h"

#define MAX_LENGHT 64

void set_time(struct tm *new_time)
{
    struct timeval new_tv = {.tv_sec = mktime(new_time), .tv_usec = 0};
    settimeofday(&new_tv, NULL);
}

void get_time()
{
    time_t now = time(NULL);
    struct tm *timeinfo = localtime(&now);
    char datetime[32];
    strftime(datetime, sizeof(datetime), "%Y-%m-%d %H:%M:%S", timeinfo);
    printf("The current datetime: %s\n", datetime);
}

static int read_char(void)
{
    int ch = EOF;
    do
    {
        ch = getchar();
    } while (ch == EOF);

    return ch;
}

void app_main()
{
    //  disable watchdog
    ESP_ERROR_CHECK(esp_task_wdt_delete(xTaskGetIdleTaskHandle()));

    char input[MAX_LENGHT];

    struct tm timeinfo = {
        .tm_sec = 10,
        .tm_min = 10,
        .tm_hour = 10,
        .tm_mday = 21,
        .tm_mon = 3 - 1,
        .tm_year = 2025 - 1900,
    };

    set_time(&timeinfo);

    while (1)
    {
        while (EOF != getchar())
        {
            ;
        }

        printf("\nS) Set date and time\nG) Get date and time\nEnter a command: ");
        int command = toupper(read_char());

        if (command == 'S')
        {
            struct tm new_time = {0};
            printf("Enter date and time (YYYY-MM-DD hh:mm:ss): ");
            int i = 0;

            while (i < MAX_LENGHT - 1)
            {
                int ch = read_char();
                if (ch == '\n')
                {
                    break;
                }
                input[i++] = ch;
                putchar(ch);
            }
            input[i] = '\0';

            sscanf(input, "%d-%d-%d %d:%d:%d",
                   &new_time.tm_year, &new_time.tm_mon, &new_time.tm_mday,
                   &new_time.tm_hour, &new_time.tm_min, &new_time.tm_sec);

            new_time.tm_year -= 1900;
            new_time.tm_mon -= 1;
            set_time(&new_time);
        }
        else if (command == 'G')
        {
            get_time();
        }
        else
        {
            printf("Invalid command!\n");
        }
    }
}