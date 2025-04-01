#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <sys/time.h>
#include "esp_sntp.h"

void set_time(struct tm *new_time) {
    struct timeval new_tv = { .tv_sec = mktime(new_time), .tv_usec = 0 };
    settimeofday(&new_tv, NULL);
}

void get_time() {
    time_t now = time(NULL);
    struct tm *timeinfo = localtime(&now);
    char datetime[32];
    strftime(datetime, sizeof(datetime), "%Y-%m-%d %H:%M:%S", timeinfo);
    printf("The current datetime: %s\n", datetime);
}

void app_main() {
    struct tm timeinfo = {
        .tm_sec = 10,
        .tm_min = 10,
        .tm_hour = 10,
        .tm_mday = 21,
        .tm_mon = 3 - 1,
        .tm_year = 2025 - 1900,
    };

    set_time(&timeinfo);

    while (1) {
        printf("\nS) Set date and time\nG) Get date and time\nEnter a command: ");
        char command = getchar();
        getchar(); // Consume newline

        if (command == 'S' || command == 's') {
            struct tm new_time = {0};
            printf("Enter date and time (YYYY-MM-DD hh:mm:ss): ");
            scanf("%d-%d-%d %d:%d:%d", 
                  &new_time.tm_year, &new_time.tm_mon, &new_time.tm_mday,
                  &new_time.tm_hour, &new_time.tm_min, &new_time.tm_sec);
            getchar(); // Consume newline
            new_time.tm_year -= 1900;
            new_time.tm_mon -= 1;
            set_time(&new_time);
        } else if (command == 'G' || command == 'g') {
            get_time();
        } else {
            printf("Invalid command!\n");
        }
    }
}
