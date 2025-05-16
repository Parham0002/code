#include "bsp.h"
#include "button.h"

#define SAMPLES (5U)

static uint8_t sample_history = 0xFF; // 5 bits, initialized to released (all 1s)
static int button_pin = -1;
static int debounced_state = BUTTON_RELEASED;
static int last_stable_state = BUTTON_RELEASED;
static int edge_state = BUTTON_RELEASED;
static bool initialized = false;

bool button_init(int pin)
{
    if (bsp_pin_config(pin, BSP_MODE_INPUT, BSP_PULL_UP))
    {
        button_pin = pin;
        sample_history = 0xFF;
        debounced_state = BUTTON_RELEASED;
        last_stable_state = BUTTON_RELEASED;
        edge_state = BUTTON_RELEASED;
        initialized = true;
        return true;
    }
    return false;
}
void button_update_state(void)
{
    if (!initialized)
        return;

    int raw_value = bsp_pin_read(button_pin);
    sample_history = ((sample_history << 1) | (raw_value & 0x01)) & 0x1F; // keep 5 bits

    if (sample_history == 0x00) // 5 LOW samples
    {
        debounced_state = BUTTON_PRESSED;
    }
    else if (sample_history == 0x1F) // 5 HIGH samples
    {
        debounced_state = BUTTON_RELEASED;
    }

    if (debounced_state != last_stable_state)
    {
        if (debounced_state == BUTTON_PRESSED)
        {
            edge_state = BUTTON_FALLING_EDGE;
        }
        else
        {
            edge_state = BUTTON_RISING_EDGE;
        }
        last_stable_state = debounced_state;
    }
    else
    {
        edge_state = debounced_state;
    }
}

    int button_get_state(void)
    {
        if (!initialized)
            return BUTTON_UNINITITIALIZED;

        int state_to_return = edge_state;

        // Only return edge once
        if (edge_state == BUTTON_FALLING_EDGE || edge_state == BUTTON_RISING_EDGE)
        {
            edge_state = last_stable_state;
        }

        return state_to_return;
    }
