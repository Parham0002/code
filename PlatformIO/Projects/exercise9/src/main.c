#include <stdio.h>
#include <driver/gpio.h>
#include <esp_timer.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/queue.h>
#include <stdatomic.h>

#define DEBOUNCE_TIME_MS 250 // 250ms debounce time
#define GPIO_BUTTON GPIO_NUM_4

static QueueHandle_t gpio_evt_queue = NULL;      // Queue to send button events
static _Atomic uint32_t last_interrupt_time = 0; // Use atomic for thread safety

// Interrupt handler for GPIO
static void IRAM_ATTR gpio_isr_handler(void *arg)
{
    uint32_t current_time = esp_timer_get_time() / 1000; // Convert to milliseconds

    if (current_time - atomic_load(&last_interrupt_time) > DEBOUNCE_TIME_MS)
    {
        atomic_store(&last_interrupt_time, current_time);

        int event = 1;
        xQueueSendFromISR(gpio_evt_queue, &event, NULL); // Send event to task
    }
}

// Task to process button press events
void button_task(void *arg)
{
    int event;
    while (1)
    {
        if (xQueueReceive(gpio_evt_queue, &event, portMAX_DELAY))
        {
            printf("Falling edge \n"); // Safe to print here
        }
    }
}

void app_main(void)
{
    // Configure GPIO4 as input with pull-up and falling edge interrupt
    ESP_ERROR_CHECK(gpio_reset_pin(GPIO_BUTTON));
    ESP_ERROR_CHECK(gpio_set_direction(GPIO_BUTTON, GPIO_MODE_INPUT));
    ESP_ERROR_CHECK(gpio_set_pull_mode(GPIO_BUTTON, GPIO_PULLUP_ONLY));
    ESP_ERROR_CHECK(gpio_set_intr_type(GPIO_BUTTON, GPIO_INTR_NEGEDGE));

    // Create queue for ISR-to-task communication
    gpio_evt_queue = xQueueCreate(10, sizeof(int));

    // Install ISR service and add the handler
    ESP_ERROR_CHECK(gpio_install_isr_service(0));
    ESP_ERROR_CHECK(gpio_isr_handler_add(GPIO_BUTTON, gpio_isr_handler, NULL));

    // Create task to process button events
    xTaskCreate(button_task, "button_task", 2048, NULL, 10, NULL);

    // Main loop (optional idle task)
    while (1)
    {
        vTaskDelay(pdMS_TO_TICKS(1000)); // Prevent watchdog reset
    }
}

