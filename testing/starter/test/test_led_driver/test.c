#include "unity.h"
#include "led_driver.h"

void setUp(void) {}
void tearDown(void) {}

void test_led_driver_on_off(void)
{
    const int TEST_PIN = 5;

    TEST_ASSERT_TRUE(led_driver_init(TEST_PIN));
    TEST_ASSERT_TRUE(led_driver_set_state(1));
    TEST_ASSERT_TRUE(led_driver_set_state(0));
}

void app_main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_led_driver_on_off);
    UNITY_END();
}
