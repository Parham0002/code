#include <stdio.h>
#include <esp_timer.h>
#include <driver/gpio.h>
#include <esp_task_wdt.h>

#define LED_PIN GPIO_NUM_4

// Metro class to handle timed tasks
class Metro
{
private:
    int64_t interval_us;
    int64_t previous_time_us;

public:
    Metro(int64_t interval_ms)
    {
        interval_us = interval_ms * 1000; // Convert ms to us
        previous_time_us = esp_timer_get_time();
    }

    bool check()
    {
        int64_t current_time = esp_timer_get_time();
        if (current_time - previous_time_us >= interval_us)
        {
            previous_time_us = current_time;
            return true;
        }
        return false;
    }
};

// Create Metro instances for tasks
Metro ledTask(500);    // 500ms interval for LED toggling
Metro printTask(1000); // 1000ms interval for printing message

extern "C" void app_main(void)
{
    // Disable Watchdog Timer for the Idle Task
    ESP_ERROR_CHECK(esp_task_wdt_delete(xTaskGetIdleTaskHandle()));

    // Configure LED pin as an output
    ESP_ERROR_CHECK(gpio_reset_pin(LED_PIN));
    ESP_ERROR_CHECK(gpio_set_direction(LED_PIN, GPIO_MODE_INPUT_OUTPUT));

    while (1)
    {
        // LED Toggle Task
        if (ledTask.check())
        {
            gpio_set_level(LED_PIN, !gpio_get_level(LED_PIN));
            printf("LED state at %lld μs = %d\n", esp_timer_get_time(), gpio_get_level(LED_PIN));
        }

        // Print "Hello, World!" Task
        if (printTask.check())
        {
            printf("Hello, World!\n");
        }

        // Simulate another workload
        int delay_count = 0xFFFF;
        while (delay_count > 0) {
            delay_count--;
        }
    }
}
