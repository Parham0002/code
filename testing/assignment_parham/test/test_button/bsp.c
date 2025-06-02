#include "bsp.h"

static int simulated_level = BSP_HIGH;

// Store last config for verification
static int last_configured_pin = -1;
static int last_configured_mode = -1;
static int last_configured_pull = -1;

bool bsp_pin_config(int pin, int mode, int pull)
{
    last_configured_pin = pin;
    last_configured_mode = mode;
    last_configured_pull = pull;
    // Always succeed in tests
    return true;
}

int bsp_pin_read(int pin)
{
    return simulated_level;
}

// Helper function for tests
void bsp_test_set_pin_level(int level)
{
    simulated_level = level;
}

int bsp_test_get_last_configured_pin(void)
{
    return last_configured_pin;
}
int bsp_test_get_last_pin_mode(void)
{
    return last_configured_mode;
}
int bsp_test_get_last_pin_pull(void)
{
    return last_configured_pull;
}
