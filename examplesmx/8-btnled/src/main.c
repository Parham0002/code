/**
 * @file main.c
 * @author Faroch Mehri (faroch.mehri@ya.se)
 * @brief An example of turning a LED connected to J2:17(P0_24) on using a push button connected to J2:11(P0_25).
 *        Look at: https://docs.zephyrproject.org/latest/build/dts/zephyr-user-node.html
 *                 https://docs.zephyrproject.org/latest/doxygen/html/group__gpio__interface.html
 *                 https://docs.zephyrproject.org/latest/build/dts/howtos.html#set-devicetree-overlays
 *                 https://docs.zephyrproject.org/latest/build/dts/index.html
 *
 * @version 0.1
 * @date 2025-03-22
 *
 * @copyright Copyright (c) 2025
 *
 */
#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/sys/__assert.h>

#define ZEPHYR_USER_NODE DT_PATH(zephyr_user)

int main(void)
{
	const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(ZEPHYR_USER_NODE, led_gpios);
	const struct gpio_dt_spec button = GPIO_DT_SPEC_GET(ZEPHYR_USER_NODE, btn_gpios);

	__ASSERT(gpio_is_ready_dt(&led), "LED) GPIO port is not ready!");
	__ASSERT(gpio_is_ready_dt(&button), "BTN) GPIO port is not ready!");

	__ASSERT(0 == gpio_pin_configure_dt(&button, GPIO_INPUT), "BTN) Failed to configure the gpio pin");
	__ASSERT(0 == gpio_pin_configure_dt(&led, GPIO_OUTPUT_INACTIVE), "LED) Failed to configure the gpio pin");

	while (1)
	{
		(void)gpio_pin_set(led.port, led.pin, (GPIO_ACTIVE_LOW == gpio_pin_get_dt(&button)));
	}

	return 0;
}
