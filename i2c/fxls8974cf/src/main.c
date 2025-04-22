/**
 * @file main.c
 * @author Faroch Mehri (faroch.mehri@ya.se)
 * @brief An example of FXLS8974CF sensor on I2C.
 *        Look at: https://www.nxp.com/docs/en/data-sheet/FXLS8974CF.pdf
 *
 * @version 0.1
 * @date 2025-02-09
 *
 * @copyright Copyright (c) 2025
 *
 */
#include <stdlib.h>
#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/sensor.h>

#define ACCEL_NODE DT_NODELABEL(fxls8974cf)

int main(void)
{
	const struct device *accel_dev = DEVICE_DT_GET(ACCEL_NODE);

	if (!device_is_ready(accel_dev))
	{
		printk("I2C device not found!\n");
		exit(EXIT_FAILURE);
	}

	struct sensor_value accel_x, accel_y, accel_z;

	while (1)
	{
		if (0 == sensor_sample_fetch(accel_dev))
		{
			if ((0 == sensor_channel_get(accel_dev, SENSOR_CHAN_ACCEL_X, &accel_x)) &&
				(0 == sensor_channel_get(accel_dev, SENSOR_CHAN_ACCEL_Y, &accel_y)) &&
				(0 == sensor_channel_get(accel_dev, SENSOR_CHAN_ACCEL_Z, &accel_z)))
			{
				printk("Acceleration (m/s^2): X: %.06f, Y: %.06f, Z: %.06f\n\n",
					   accel_x.val1 + accel_x.val2 * 0.000001,
					   accel_y.val1 + accel_y.val2 * 0.000001,
					   accel_z.val1 + accel_z.val2 * 0.000001);
			}
			else
			{
				printk("Failed to read the sensor values\n");
			}
		}
		else
		{
			printk("Failed to fetch sensor data\n");
		}

		k_sleep(K_MSEC(1000));
	}

	return 0;
}
