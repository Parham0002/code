#include "terminal.h"
#include "bsp.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

bool terminal_init(void)
{
    // Configure the LED pin as input/output
    if (!bsp_pin_config(TERMINAL_LED_PIN, BSP_PIN_INPUT_OUTPUT))
    {
        bsp_console_print("Failed to configure LED pin\n");
        return false;
    }

    return true;
}
bool terminal_run(void)
{
    int input;
    int retries = 10;

    bsp_console_print(TERMINAL_COMMAND_MSG);

    while ((input = bsp_console_getchar()) == BSP_CONSOLE_EOF && retries-- > 0)
    {
        vTaskDelay(pdMS_TO_TICKS(1000)); // wait 100ms
    }

    if (input == BSP_CONSOLE_EOF)
    {
        bsp_console_print("No input detected\n");
        return false;
    }
    char cmd = (char)input;

    switch (cmd)
    {
    case TERMINAL_LED_ON:
        if (bsp_pin_write(TERMINAL_LED_PIN, 1))
        {
            bsp_console_print("Turning LED ON");
            bsp_console_print(TERMINAL_DONE_MSG);
        }
        else
        {
            bsp_console_print("Failed to turn LED ON");
            bsp_console_print(TERMINAL_FAILED_MSG);
        }
        break;

    case TERMINAL_LED_OFF:
        if (bsp_pin_write(TERMINAL_LED_PIN, 0))
        {
            bsp_console_print("Turning LED OFF");
            bsp_console_print(TERMINAL_DONE_MSG);
        }
        else
        {
            bsp_console_print("Failed to turn LED OFF");
            bsp_console_print(TERMINAL_FAILED_MSG);
        }
        break;

    default:
        bsp_console_print("Invalid input. Try again.\n");
        return false;
    }

    return true;
}
