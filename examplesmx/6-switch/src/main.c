/**
 * @file main.c
 * @author Faroch Mehri (faroch.mehri@ya.se)
 * @brief An example of using user_button_3(sw1) on the board.
 *        Look at: https://docs.zephyrproject.org/latest/build/dts/api/bindings/input/gpio-keys.html
 *                 https://docs.zephyrproject.org/latest/samples/basic/button/README.html
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

#define BUTTON0_NODE DT_ALIAS(sw1) // The devicetree node identifier for the "sw1" alias.

int main(void)
{
	const struct gpio_dt_spec button = GPIO_DT_SPEC_GET(BUTTON0_NODE, gpios);

	__ASSERT(gpio_is_ready_dt(&button), "GPIO port is not ready!");

	__ASSERT(0 == gpio_pin_configure_dt(&button, GPIO_INPUT), "Failed to configure the gpio pin");

	int current_state;
	uint32_t count = 0;
	uint32_t previous_count = 0;
	int previous_state = GPIO_ACTIVE_HIGH;

	while (1)
	{
		current_state = gpio_pin_get_dt(&button);

		if (current_state != previous_state)
		{
			if (current_state == GPIO_ACTIVE_LOW)
			{
				count++;
			}
			previous_state = current_state;
		}
		else if (count != previous_count)
		{
			printf("count: %u\n", count);
			previous_count = count;
		}
		else
		{
			;
		}
	}

	return 0;
}
