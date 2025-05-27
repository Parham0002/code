#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/i2c.h>

#define I2C_SLAVE_NODE DT_ALIAS(i2c_slave)

#if !DT_NODE_HAS_STATUS(I2C_SLAVE_NODE, okay)
#error "I2C slave device not found in device tree"
#endif

int main(void)
{
	const struct device *i2c_dev = DEVICE_DT_GET(I2C_SLAVE_NODE);

	if (!device_is_ready(i2c_dev))
	{
		printk("I2C device not ready\n");
		return 1;
	}

	printk("I2C slave device is ready: %s\n", i2c_dev->name);

	while (1)
	{
		k_msleep(1000);
	}

	return 0;
}
