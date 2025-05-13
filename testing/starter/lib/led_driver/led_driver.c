#include "bsp.h"
#include "led_driver.h"

static int led_pin = -1;

bool led_driver_init(int pin)
{
    led_pin = pin;
    return bsp_pin_config(pin, BSP_PIN_INPUT_OUTPUT);
}

bool led_driver_set_state(int state)
{
    if (led_pin == -1){
        return false;
    }
    return bsp_pin_write(led_pin, state);
}