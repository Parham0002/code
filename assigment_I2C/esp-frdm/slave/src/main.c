#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/i2c.h>
#include <zephyr/sys/printk.h>

#define I2C_DEV DT_NODELABEL(flexcomm2)

void app_main(void)
{
	const struct device *i2c_dev = DEVICE_DT_GET(I2C_DEV);

	if (!device_is_ready(i2c_dev))
	{
		printk("I2C device not ready\n");
		exit(1);
	}

	printk("I2C device ready\n");

	uint8_t buffer[16];

	while (1)
	{
		int ret = i2c_read(i2c_dev, buffer, sizeof(buffer), 0x55);
		if (ret == 0)
		{
			printk("Received: %s\n", buffer);
		}
		else
		{
			printk("I2C read failed: %d\n", ret);
		}
		k_msleep(1000);
	}
}
