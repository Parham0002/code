#include <stdio.h>
#include "esp_err.h"
#include "esp_adc/adc_oneshot.h"
#include "driver/ledc.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define ADC_UNIT ADC_UNIT_1
#define ADC_CHANNEL ADC_CHANNEL_0 // Potentiometer on GPIO0
#define LED_GPIO 4                // LED on GPIO4
#define MAX_ADC_VALUE 4095        // 12-bit ADC max value
#define MAX_PWM_DUTY 255          // 8-bit PWM (0-255)
#define PWM_FREQUENCY 5000        // 5 kHz PWM

adc_oneshot_unit_handle_t adc_handle;

void configure_adc()
{
    adc_oneshot_unit_init_cfg_t init_config = {
        .unit_id = ADC_UNIT,
    };
    ESP_ERROR_CHECK(adc_oneshot_new_unit(&init_config, &adc_handle));

    adc_oneshot_chan_cfg_t channel_config = {
        .atten = ADC_ATTEN_DB_0, // ✅ Fix: Use DB_0 for full 0-3.3V range
        .bitwidth = ADC_BITWIDTH_12,
    };
    ESP_ERROR_CHECK(adc_oneshot_config_channel(adc_handle, ADC_CHANNEL, &channel_config));
}

void configure_led_pwm()
{
    ledc_timer_config_t ledc_timer = {
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .timer_num = LEDC_TIMER_0,
        .duty_resolution = LEDC_TIMER_8_BIT, // 8-bit PWM
        .freq_hz = PWM_FREQUENCY,
        .clk_cfg = LEDC_AUTO_CLK,
    };
    ESP_ERROR_CHECK(ledc_timer_config(&ledc_timer));

    ledc_channel_config_t ledc_channel = {
        .gpio_num = LED_GPIO,
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .channel = LEDC_CHANNEL_0,
        .timer_sel = LEDC_TIMER_0,
        .duty = 0,
        .hpoint = 0};
    ESP_ERROR_CHECK(ledc_channel_config(&ledc_channel));
}

void adc_read_task(void *arg)
{
    while (1)
    {
        int raw_value = 0;
        ESP_ERROR_CHECK(adc_oneshot_read(adc_handle, ADC_CHANNEL, &raw_value));

        // Fix: Use correct mapping for smooth brightness
        int pwm_duty = (raw_value * MAX_PWM_DUTY) / MAX_ADC_VALUE;

        printf("ADC: %d -> PWM: %d\n", raw_value, pwm_duty); // Debugging

        ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, pwm_duty);
        ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0);

        vTaskDelay(pdMS_TO_TICKS(50)); // Reduce delay for smoother changes
    }
}

void app_main()
{
    configure_adc();
    configure_led_pwm();
    xTaskCreate(adc_read_task, "adc_read_task", 4096, NULL, 5, NULL);
}

/*#include "esp_adc/adc_oneshot.h"

#define POT_PIN ADC1_CHANNEL_0   // GPIO0 (ADC1_CH0)

// ADC configuration (new API)
adc_oneshot_unit_handle_t adc1_handle = NULL;
adc_oneshot_config_t adc1_config = {
    .width = ADC_WIDTH_BIT_12,           // 12-bit resolution
    .adc2_channel = ADC2_CHANNEL_0,      // Use ADC1 channel 0
    .adc_characteristics = ADC1_ATTEN_DB_0, // 0 dB attenuation (input range: 0-3.3V)
};

void app_main(void) {
    // Initialize the ADC
    ESP_ERROR_CHECK(adc_oneshot_new_unit(&adc1_config, &adc1_handle));

    // Setup PWM for LED (already covered in previous code)

    while (1) {
        // Read potentiometer value (0-4095)
        int pot_value = 0;
        adc_oneshot_read(adc1_handle, POT_PIN, &pot_value);

        // Map potentiometer value to PWM range (0-255)
        int pwm_value = (pot_value * 255) / 4095;

        // Set the LED brightness (PWM duty cycle)
        ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, pwm_value);
        ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0);

        // Small delay
        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
}

*/