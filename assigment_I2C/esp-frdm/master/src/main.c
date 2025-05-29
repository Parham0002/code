#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include "driver/i2c.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include <driver/i2c_master.h>
#include <esp_task_wdt.h>

#define MAX_LEN 5
#define MASTER I2C_NUM_0
#define PIN_SDA GPIO_NUM_6 // GPIO for SDA
#define PIN_SCL GPIO_NUM_7 // GPIO for SCL
#define CLOCK_RATE 400000  // Communication Speed
#define SLAVE_ADDRESS 0x55 // Slave Address
#define MSG_SIZE 8         // Buffer Length

void get_led_state(uint8_t *buffer, size_t len)
{
    while (getchar() != EOF)
        ;

    int i = 0;
    char ch = 0;
    while (1)
    {
        ch = getchar();
        if ((ch == '\n') && (i == 0))
        {
            printf("Enter the LED state (off, red, green, blue): ");
        }
        else if (ch == '\n')
        {
            break;
        }
        else if (ch >= 'a' && ch <= 'z')
        {
            putchar(ch); // Echo character
            buffer[i++] = ch;
        }
        else
        {
        }
    }
    buffer[i] = '\0';
}

void app_main(void)
{
    ESP_ERROR_CHECK(esp_task_wdt_deinit());
    i2c_master_bus_handle_t bus_handle;
    i2c_master_bus_config_t bus_config = {
        .i2c_port = MASTER,
        .sda_io_num = PIN_SDA,
        .scl_io_num = PIN_SCL,
        .clk_source = I2C_CLK_SRC_DEFAULT,
        .glitch_ignore_cnt = 7,
        .flags.enable_internal_pullup = true,
    };
    ESP_ERROR_CHECK(i2c_new_master_bus(&bus_config, &bus_handle));

    i2c_master_dev_handle_t dev_handle;
    i2c_device_config_t dev_config = {
        .dev_addr_length = I2C_ADDR_BIT_LEN_7,
        .device_address = SLAVE_ADDRESS,
        .scl_speed_hz = CLOCK_RATE,
    };
    ESP_ERROR_CHECK(i2c_master_bus_add_device(bus_handle, &dev_config, &dev_handle));

    uint8_t buffer[MAX_LEN + 1];
    while (1)
    {
        printf("Enter the LED state (off, red, green, blue): ");
        get_led_state(buffer, sizeof(buffer));

        strcat((char *)buffer, "\n");

        if (ESP_OK == i2c_master_transmit(dev_handle, buffer, strlen((char *)buffer), -1))
        {
            if (ESP_OK == i2c_master_receive(dev_handle, buffer, MAX_LEN, -1))
            {
                if (strcmp((const char *)buffer, "ok") == 0)
                {
                    printf(" => done");
                }
                else if (strcmp((const char *)buffer, "fail") == 0)
                {
                    printf(" => failed");
                }
                else
                {
                }
            }
            else
            {
                printf("Failed Recieved");
            }
            printf("\n");
        }
        else
        {
            printf("Failed Transmit");
        }
        printf("\n");
    }
}
