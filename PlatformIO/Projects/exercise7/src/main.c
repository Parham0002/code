#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <driver/ledc.h>

#define LEDC_TIMER LEDC_TIMER_0
#define LEDC_MODE LEDC_LOW_SPEED_MODE
#define LEDC_DUTY_RES LEDC_TIMER_13_BIT // Duty resolution
#define LEDC_FREQUENCY (5000)           // PWM frequency in Hertz
#define LEDC_DUTY_PERCENT_TO_VALUE(p) (uint32_t)(((p) / 100.0f) * (1 << LEDC_DUTY_RES))

#define GPIO_RED GPIO_NUM_4   // GPIO for Red LED
#define GPIO_GREEN GPIO_NUM_5 // GPIO for Green LED
#define GPIO_BLUE GPIO_NUM_6  // GPIO for Blue LED

// Function to configure the LEDC PWM channel
void configure_ledc_channel(ledc_channel_t channel, gpio_num_t gpio, ledc_timer_t timer)
{
    ledc_channel_config_t ledc_channel = {
        .speed_mode = LEDC_MODE,
        .channel = channel,
        .timer_sel = timer,
        .intr_type = LEDC_INTR_DISABLE,
        .gpio_num = gpio,
    };
    ESP_ERROR_CHECK(ledc_channel_config(&ledc_channel));
}

void app_main(void)
{
    // Seed the random number generator
    srand(time(NULL));

    // Prepare and then apply the LEDC PWM timer configuration
    ledc_timer_config_t ledc_timer = {
        .speed_mode = LEDC_MODE,
        .timer_num = LEDC_TIMER,
        .duty_resolution = LEDC_DUTY_RES,
        .freq_hz = LEDC_FREQUENCY, // Set output frequency at 5 kHz
        .clk_cfg = LEDC_AUTO_CLK};
    ESP_ERROR_CHECK(ledc_timer_config(&ledc_timer));

    // Configure the three LEDC channels for RGB LEDs
    configure_ledc_channel(LEDC_CHANNEL_0, GPIO_RED, LEDC_TIMER);   // Red LED on GPIO4
    configure_ledc_channel(LEDC_CHANNEL_1, GPIO_GREEN, LEDC_TIMER); // Green LED on GPIO5
    configure_ledc_channel(LEDC_CHANNEL_2, GPIO_BLUE, LEDC_TIMER);  // Blue LED on GPIO6

    while (1)
    {
        // Generate random PWM values for RGB colors (0 to 100%)
        uint32_t red_pwm = LEDC_DUTY_PERCENT_TO_VALUE(rand() % 101);   // Random duty for Red (0-100%)
        uint32_t green_pwm = LEDC_DUTY_PERCENT_TO_VALUE(rand() % 101); // Random duty for Green (0-100%)
        uint32_t blue_pwm = LEDC_DUTY_PERCENT_TO_VALUE(rand() % 101);  // Random duty for Blue (0-100%)

        // Set the random PWM values for the RGB LEDs
        ESP_ERROR_CHECK(ledc_set_duty(LEDC_MODE, LEDC_CHANNEL_0, red_pwm));   // Red LED
        ESP_ERROR_CHECK(ledc_set_duty(LEDC_MODE, LEDC_CHANNEL_1, green_pwm)); // Green LED
        ESP_ERROR_CHECK(ledc_set_duty(LEDC_MODE, LEDC_CHANNEL_2, blue_pwm));  // Blue LED

        // Update the duty cycle to apply the new values
        ESP_ERROR_CHECK(ledc_update_duty(LEDC_MODE, LEDC_CHANNEL_0));
        ESP_ERROR_CHECK(ledc_update_duty(LEDC_MODE, LEDC_CHANNEL_1));
        ESP_ERROR_CHECK(ledc_update_duty(LEDC_MODE, LEDC_CHANNEL_2));

        // Wait for 1 second before changing the color again
        sleep(1);
    }
}
