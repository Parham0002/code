/**
 * @file main.c
 * @author Faroch Mehri (faroch.mehri@ya.se)
 * @brief An example of a bouncing push button connected to J2:17(P0_24).
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
	const struct gpio_dt_spec button = GPIO_DT_SPEC_GET(ZEPHYR_USER_NODE, button_gpios);

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
