/**
 * @file main.c
 * @author Faroch Mehri (faroch.mehri@ya.se)
 * @brief An example of using an event(e.g. pressing a key) and number of the system ticks to seed the standard random number generator.
 *
 * @version 0.1
 * @date 2025-03-29
 *
 * @copyright Copyright (c) 2025
 *
 */
#include <stdlib.h>
#include <zephyr/kernel.h>
#include <zephyr/sys_clock.h>
#include <zephyr/logging/log.h>
#include <zephyr/console/console.h>

LOG_MODULE_REGISTER(random);

int main(void)
{
	if (0 != console_init())
	{
		LOG_ERR("Error: failed to init console");
		return EXIT_FAILURE;
	}

	printk("Press any key to continue ...");
	if (0 > console_getchar())
	{
		LOG_ERR("Error: failed to read from console");
		return EXIT_FAILURE;
	}

	srand((uint32_t)k_uptime_ticks());

	while (1)
	{
		printf("Random Number = %010d\n", rand());

		k_sleep(K_MSEC(500));
	}

	return 0;
}
