/**
 * @file main.c
 * @author Faroch Mehri (faroch.mehri@ya.se)
 * @brief An example of getting the current datetime from an NTP server and set the internal RTC datetime.
 *        Look at: https://docs.espressif.com/projects/esp-idf/en/latest/esp32c6/api-reference/system/system_time.html
 *
 * @version 0.1
 * @date 2025-03-22
 *
 * @copyright Copyright (c) 2025
 *
 */
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include "esp_log.h"
#include "esp_wifi.h"
#include "esp_sntp.h"
#include "esp_event.h"
#include "nvs_flash.h"

#define WIFI_SSID "MaxPlus"
#define WIFI_PASS "SV21TRC3556"

static const char *TAG = "wifi_sntp";

void time_sync_notification_cb(struct timeval *tv)
{
    (void)tv;
    ESP_LOGI(TAG, "Notification of a time synchronization event");
}

void initialize_sntp(void)
{
    ESP_LOGI(TAG, "Initializing SNTP");
    esp_sntp_setoperatingmode(SNTP_OPMODE_POLL);
    esp_sntp_setservername(0, "pool.ntp.org");
    esp_sntp_set_time_sync_notification_cb(time_sync_notification_cb);
    esp_sntp_init();
}

void obtain_time(void)
{
    initialize_sntp();

    // https://www.gnu.org/software/libc/manual/html_node/TZ-Variable.html
    // https://support.cyberdata.net/portal/en/kb/articles/010d63c0cfce3676151e1f2d5442e311
    // E.g. zdump -v /usr/share/zoneinfo/Europe/Stockholm | grep 2025
    //      zdump -i /usr/share/zoneinfo/Europe/Stockholm | grep 2026
    /**
      with open("/usr/share/zoneinfo/Europe/Stockholm", "rb") as file:
        content = file.readlines()
        print(content[-1].decode("ASCII").strip("\n"))
    */
    setenv("TZ", "CET-1CEST,M3.5.0/02:00:00,M10.5.0/03:00:00", 1);
    tzset();

    // Wait for time to be set
    time_t now = 0;
    struct tm timeinfo = {0};
    const int this_year = atoi(__DATE__ + 7) - 1900;

    while (timeinfo.tm_year < this_year)
    {
        (void)time(&now);
        (void)localtime_r(&now, &timeinfo);
        vTaskDelay(2000 / portTICK_PERIOD_MS);
        ESP_LOGI(TAG, "Waiting for system time to be set ...");
    }

    ESP_LOGI(TAG, "Time is set: %s", asctime(&timeinfo));
}

static void event_handler(void *arg, esp_event_base_t event_base, int32_t event_id, void *event_data)
{
    if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_START)
    {
        esp_wifi_connect();
    }
    else if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_DISCONNECTED)
    {
        esp_wifi_connect();
        ESP_LOGI(TAG, "Retrying to connect to the AP");
    }
    else if (event_base == IP_EVENT && event_id == IP_EVENT_STA_GOT_IP)
    {
        ESP_LOGI(TAG, "Connected to AP, start SNTP");
        obtain_time();
    }
}

void wifi_init_sta(void)
{
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());

    esp_netif_t *sta_netif = esp_netif_create_default_wifi_sta();
    assert(sta_netif != NULL);

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));

    ESP_ERROR_CHECK(esp_event_handler_instance_register(WIFI_EVENT, ESP_EVENT_ANY_ID, &event_handler, NULL, NULL));
    ESP_ERROR_CHECK(esp_event_handler_instance_register(IP_EVENT, IP_EVENT_STA_GOT_IP, &event_handler, NULL, NULL));

    wifi_config_t wifi_config = {
        .sta = {
            .ssid = WIFI_SSID,
            .password = WIFI_PASS,
        },
    };
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_set_config(ESP_IF_WIFI_STA, &wifi_config));
    ESP_ERROR_CHECK(esp_wifi_start());

    ESP_LOGI(TAG, "wifi_init_sta finished.");
}

void app_main(void)
{
    // Initialize NVS
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
    {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

    ESP_LOGI(TAG, "ESP_WIFI_MODE_STA");
    wifi_init_sta();

    while (1)
    {
        time_t now = time(NULL);
        char datetime[32] = {0};
        struct tm *timeinfo = localtime(&now);

        // For details of strftime look at: https://en.cppreference.com/w/c/chrono/strftime
        strftime(datetime, sizeof(datetime), "%Y-%m-%d %H:%M:%S", timeinfo);

        printf("The current datetime: %s\n", datetime);

        sleep(1); // 1 second delay
    }
}
