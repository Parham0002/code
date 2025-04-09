#include <stdio.h>
#include <unistd.h>
#include <esp_log.h>
#include <esp_attr.h>
#include <driver/gpio.h>
#include <driver/gptimer.h>
#include <driver/ledc.h>

#define INTERVAL 50000 // 50ms interval for GPTimer
#define LEDC_CHANNEL LEDC_CHANNEL_0
#define LEDC_TIMER LEDC_TIMER_0
#define LEDC_SPEED LEDC_LOW_SPEED_MODE    // Use low speed mode for PWM
#define LEDC_RESOLUTION LEDC_TIMER_13_BIT // 13-bit resolution for PWM (0 to 8191)
#define LEDC_FREQUENCY 1000               // PWM Frequency set to 1 kHz

static const char *TAG = "LED_Fade";
static int brightness = 0; // PWM brightness level (0-8191)
static int step = 5;       // Fade step size (5% of max value)

static bool timer_on_alarm(gptimer_handle_t timer, const gptimer_alarm_event_data_t *edata, void *user_data)
{
    (void)edata;
    (void)timer;
    (void)user_data;

    // Fade the brightness by 5% in either direction
    brightness += step;
    if (brightness >= 8191 || brightness <= 0)
    {
        // Reverse direction if brightness reaches limits
        step = -step;
    }

    // Update PWM duty cycle to control LED brightness
    ledc_set_duty(LEDC_SPEED, LEDC_CHANNEL, brightness);
    ledc_update_duty(LEDC_SPEED, LEDC_CHANNEL);

    return true; // No need to yield at the end of ISR
}

void app_main(void)
{
    ESP_LOGI(TAG, "Configuring PWM on GPIO4");

    // Set up PWM for LED on GPIO4
    ledc_timer_config_t ledc_timer = {
        .duty_resolution = LEDC_RESOLUTION, // Resolution of PWM
        .freq_hz = LEDC_FREQUENCY,          // Frequency of PWM
        .speed_mode = LEDC_SPEED,           // Speed mode (low speed)
        .timer_num = LEDC_TIMER,            // Timer number
    };
    ESP_ERROR_CHECK(ledc_timer_config(&ledc_timer));

    ledc_channel_config_t ledc_channel = {
        .channel = LEDC_CHANNEL,
        .duty = brightness,       // Start with 0% brightness
        .gpio_num = GPIO_NUM_4,   // GPIO4 is used for the LED
        .speed_mode = LEDC_SPEED, // Speed mode
        .hpoint = 0,              // No hold point
        .timer_sel = LEDC_TIMER,  // Timer select
    };
    ESP_ERROR_CHECK(ledc_channel_config(&ledc_channel));

    ESP_LOGI(TAG, "Creating GPTimer handle");

    // Configure GPTimer to trigger every 50ms
    gptimer_handle_t gptimer = NULL;
    gptimer_config_t timer_config = {
        .clk_src = GPTIMER_CLK_SRC_DEFAULT,
        .direction = GPTIMER_COUNT_UP,
        .resolution_hz = 1000000, // 1 MHz, 1 tick = 1 us
    };
    ESP_ERROR_CHECK(gptimer_new_timer(&timer_config, &gptimer));

    ESP_LOGI(TAG, "Register the event handler");
    gptimer_event_callbacks_t cbs = {
        .on_alarm = timer_on_alarm,
    };
    ESP_ERROR_CHECK(gptimer_register_event_callbacks(gptimer, &cbs, NULL));

    ESP_LOGI(TAG, "Enable timer");
    ESP_ERROR_CHECK(gptimer_enable(gptimer));

    ESP_LOGI(TAG, "Start timer with 50ms interval");
    gptimer_alarm_config_t alarm_config = {
        .reload_count = 0,
        .alarm_count = INTERVAL, // 50ms period
        .flags.auto_reload_on_alarm = true,
    };
    ESP_ERROR_CHECK(gptimer_set_alarm_action(gptimer, &alarm_config));
    ESP_ERROR_CHECK(gptimer_start(gptimer));

    while (1)
    {
        // Main loop can be used for other tasks if needed
        printf("LED brightness: %d\n", brightness);
        sleep(1); // 1 second delay for printing status (this does not affect fading)
    }
}
