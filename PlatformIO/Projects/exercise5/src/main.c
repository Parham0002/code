#include <stdio.h>
#include <unistd.h>
#include <driver/ledc.h>

#define LEDC_TIMER LEDC_TIMER_0
#define LEDC_MODE LEDC_LOW_SPEED_MODE
#define LEDC_CHANNEL LEDC_CHANNEL_0
#define LEDC_DUTY_RES LEDC_TIMER_13_BIT // 13-bit resolution
#define LEDC_FREQUENCY (4000)           // PWM frequency in Hz
#define LEDC_DUTY_PERCENT_TO_VALUE(p) (uint32_t)(((p) / 100.0f) * ((1 << LEDC_DUTY_RES) - 1))

void app_main(void)
{
    // Configure the LEDC PWM timer
    ledc_timer_config_t ledc_timer = {
        .speed_mode = LEDC_MODE,
        .timer_num = LEDC_TIMER,
        .duty_resolution = LEDC_DUTY_RES,
        .freq_hz = LEDC_FREQUENCY,
        .clk_cfg = LEDC_AUTO_CLK};
    ESP_ERROR_CHECK(ledc_timer_config(&ledc_timer));

    // Configure the LEDC PWM channel
    ledc_channel_config_t ledc_channel = {
        .speed_mode = LEDC_MODE,
        .channel = LEDC_CHANNEL,
        .timer_sel = LEDC_TIMER,
        .intr_type = LEDC_INTR_DISABLE,
        .gpio_num = GPIO_NUM_4,
        .duty = 0}; // Start with LED off
    ESP_ERROR_CHECK(ledc_channel_config(&ledc_channel));

    while (1)
    {
        // Fade in
        for (int duty = 0; duty <= 100; duty += 5)
        {
            ESP_ERROR_CHECK(ledc_set_duty(LEDC_MODE, LEDC_CHANNEL, LEDC_DUTY_PERCENT_TO_VALUE(duty)));
            ESP_ERROR_CHECK(ledc_update_duty(LEDC_MODE, LEDC_CHANNEL));
            usleep(50000); // 50 ms delay
        }

        // Fade out
        for (int duty = 100; duty >= 0; duty -= 5)
        {
            ESP_ERROR_CHECK(ledc_set_duty(LEDC_MODE, LEDC_CHANNEL, LEDC_DUTY_PERCENT_TO_VALUE(duty)));
            ESP_ERROR_CHECK(ledc_update_duty(LEDC_MODE, LEDC_CHANNEL));
            usleep(50000); // 50 ms delay
        }
    }
}
