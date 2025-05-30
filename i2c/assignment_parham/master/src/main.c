/**
 * @file main.c
 * @author Faroch Mehri (faroch.mehri@ya.se)
 * @brief An example of I2C controller in master mode.
 *        Look at: https://docs.espressif.com/projects/esp-idf/en/stable/esp32c6/api-reference/peripherals/i2c.html
 *
 * @version 0.1
 * @date 2025-04-01
 *
 * @copyright Copyright (c) 2025
 *
 */
#include <ctype.h>
#include <stdio.h>
#include <unistd.h>
#include <esp_log.h>
#include <driver/gpio.h>
#include <esp_task_wdt.h>
#include <driver/i2c_master.h>

#define MASTER I2C_NUM_0
#define PIN_SDA GPIO_NUM_6 // GPIO for SDA
#define PIN_SCL GPIO_NUM_7 // GPIO for SCL
#define CLOCK_RATE 400000  // Communication Speed
#define SLAVE_ADDRESS 0x55 // Slave Address
#define MSG_SIZE 8         // Buffer Length

static const char *TAG = "I2C_MASTER";

void app_main(void)
{
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

    ESP_LOGI(TAG, "I2C Master initialized successfully");

    while (1)
    {
        char chr;
        int i = 0;
        uint8_t buffer[MSG_SIZE] = {0};

        printf("Enter a LED state (off, red, green, blue): ");

        ESP_ERROR_CHECK(esp_task_wdt_delete(xTaskGetIdleTaskHandle()));
        while (i < sizeof(buffer) - 1)
        {
            chr = getchar();
            if (chr == '\n')
            {
                break;
            }
            else if (isalpha(chr))
            {
                putchar(chr);
                buffer[i++] = toupper(chr);
            }
            else
            {
                ;
            }
        }
        ESP_ERROR_CHECK(esp_task_wdt_add(xTaskGetIdleTaskHandle()));

        if (i > 0)
        {
            if (ESP_OK == i2c_master_transmit(dev_handle, buffer, MSG_SIZE, -1))
            {
                if (ESP_OK == i2c_master_receive(dev_handle, buffer, MSG_SIZE, -1))
                {
                    printf(" => %s", buffer);
                }
                else
                {
                    printf(" => failed");
                }
            }
            else
            {
                printf(" => failed");
            }
        }
        printf("\n");
    }
}