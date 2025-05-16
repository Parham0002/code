#include "bsp.h"

static int simulated_level = BSP_HIGH;

bool bsp_pin_config(int pin, int mode, int pull)
{
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