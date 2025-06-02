#include "bsp.h"
#include "button.h"
#include <unity.h>

void setUp(void) {}
void tearDown(void) {}

static void simulate_input(int level, int cycles)
{
    bsp_test_set_pin_level(level);
    for (int i = 0; i < cycles; i++)
    {
        button_update_state();
    }
}

void test_button_init_and_default_state(void)
{
    TEST_ASSERT_TRUE(button_init(4)); 
    TEST_ASSERT_EQUAL(BUTTON_RELEASED, button_get_state());
}

void test_button_falling_edge_and_pressed_state(void)
{
    button_init(4);

    simulate_input(BSP_LOW, 5); // Simulate press
    TEST_ASSERT_EQUAL(BUTTON_FALLING_EDGE, button_get_state());

    // Edge should only be reported once
    TEST_ASSERT_EQUAL(BUTTON_PRESSED, button_get_state());
}

void test_button_rising_edge_and_released_state(void)
{
    button_init(4);

    simulate_input(BSP_LOW, 5); // Press
    button_get_state();         // Consume FALLING_EDGE

    simulate_input(BSP_HIGH, 5); // Release
    TEST_ASSERT_EQUAL(BUTTON_RISING_EDGE, button_get_state());

    // Edge should only be reported once
    TEST_ASSERT_EQUAL(BUTTON_RELEASED, button_get_state());
}

void test_button_no_change_if_not_stable(void)
{
    button_init(4);

    bsp_test_set_pin_level(BSP_LOW);
    button_update_state(); // 1 LOW only

    TEST_ASSERT_EQUAL(BUTTON_RELEASED, button_get_state()); // Not enough samples to change
}

void test_button_init_configures_pin_correctly(void)
{
    int pin = 4;
    button_init(pin);

    TEST_ASSERT_EQUAL(pin, bsp_test_get_last_configured_pin());
    TEST_ASSERT_EQUAL(BSP_MODE_INPUT, bsp_test_get_last_pin_mode());
    TEST_ASSERT_EQUAL(BSP_PULL_UP, bsp_test_get_last_pin_pull());
}

#if defined(RUNNING_ON_PC)
int main(void)
#else
int app_main(void)
#endif
{
    UNITY_BEGIN();

    RUN_TEST(test_button_init_and_default_state);
    RUN_TEST(test_button_falling_edge_and_pressed_state);
    RUN_TEST(test_button_rising_edge_and_released_state);
    RUN_TEST(test_button_no_change_if_not_stable);

    return UNITY_END();
}
