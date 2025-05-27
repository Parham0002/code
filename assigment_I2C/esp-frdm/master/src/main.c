#include <stdio.h>
#include <string.h>
#include "driver/i2c.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

#define I2C_MASTER_NUM I2C_NUM_0
#define I2C_MASTER_SCL_IO 7
#define I2C_MASTER_SDA_IO 6
#define I2C_MASTER_FREQ_HZ 100000
#define I2C_MASTER_TX_BUF_DISABLE 0
#define I2C_MASTER_RX_BUF_DISABLE 0
#define WRITE_BIT I2C_MASTER_WRITE
#define READ_BIT I2C_MASTER_READ
#define ACK_CHECK_EN 0x1
#define SLAVE_ADDR 0x55

static esp_err_t i2c_master_init(void)
{
    i2c_config_t conf = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = I2C_MASTER_SDA_IO,
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_io_num = I2C_MASTER_SCL_IO,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .master.clk_speed = I2C_MASTER_FREQ_HZ,
    };
    ESP_ERROR_CHECK(i2c_param_config(I2C_MASTER_NUM, &conf));
    return i2c_driver_install(I2C_MASTER_NUM, conf.mode, 0, 0, 0);
}

static void send_led_state(const char *led_state)
{
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (SLAVE_ADDR << 1) | WRITE_BIT, ACK_CHECK_EN);
    i2c_master_write(cmd, (const uint8_t *)led_state, strlen(led_state), ACK_CHECK_EN);
    i2c_master_stop(cmd);
    esp_err_t ret = i2c_master_cmd_begin(I2C_MASTER_NUM, cmd, pdMS_TO_TICKS(1000));
    i2c_cmd_link_delete(cmd);

    if (ret == ESP_OK)
    {
        vTaskDelay(pdMS_TO_TICKS(100)); // Short delay before reading response
        uint8_t response[8];
        memset(response, 0, sizeof(response));
        i2c_cmd_handle_t rcmd = i2c_cmd_link_create();
        i2c_master_start(rcmd);
        i2c_master_write_byte(rcmd, (SLAVE_ADDR << 1) | READ_BIT, ACK_CHECK_EN);
        i2c_master_read(rcmd, response, sizeof(response) - 1, I2C_MASTER_LAST_NACK);
        i2c_master_stop(rcmd);
        ret = i2c_master_cmd_begin(I2C_MASTER_NUM, rcmd, pdMS_TO_TICKS(1000));
        i2c_cmd_link_delete(rcmd);

        if (ret == ESP_OK && strcmp((char *)response, "OK") == 0)
        {
            printf("=> done\n\n");
        }
        else
        {
            printf("=> failed\n\n");
        }
    }
    else
    {
        printf("=> failed\n\n");
    }
}

int app_main(void)
{
    ESP_ERROR_CHECK(i2c_master_init());

    char input[16];
    while (1)
    {
        printf("Enter the LED state (off, red, green, blue): ");
        fflush(stdout); // <--- Makes sure it's printed to serial

        // Read input from serial properly
        if (fgets(input, sizeof(input), stdin) != NULL)
        {
            // Remove newline character if present
            input[strcspn(input, "\n")] = 0;
            send_led_state(input);
        }
        else
        {
            printf("Input error\n");
        }

        vTaskDelay(pdMS_TO_TICKS(500));
    }
    return 0;
}
