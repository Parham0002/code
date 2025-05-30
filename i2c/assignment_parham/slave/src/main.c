#include <ctype.h>
#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/i2c.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/sys/__assert.h>

#define MSG_SIZE 8
#define I2C_NODE DT_PROP(DT_PATH(zephyr_user), i2c)
#define ADDRESS DT_PROP(DT_PATH(zephyr_user), address)

#define RED_LED_NODE DT_ALIAS(led0)
#define GREEN_LED_NODE DT_ALIAS(led1)
#define BLUE_LED_NODE DT_ALIAS(led2)

static const struct gpio_dt_spec red_led = GPIO_DT_SPEC_GET(RED_LED_NODE, gpios);
static const struct gpio_dt_spec green_led = GPIO_DT_SPEC_GET(GREEN_LED_NODE, gpios);
static const struct gpio_dt_spec blue_led = GPIO_DT_SPEC_GET(BLUE_LED_NODE, gpios);

static int count = 0;
static uint8_t buffer[MSG_SIZE];


static int on_write_requested(struct i2c_target_config *config) { return 0; }

static int on_write_received(struct i2c_target_config *config, uint8_t val)
{
	buffer[count] = toupper(val);
	count = (count + 1) % MSG_SIZE;
	return 0;
}


static int on_read_requested(struct i2c_target_config *config, uint8_t *val)
{
	*val = buffer[count];
	count = (count + 1) % MSG_SIZE;
	return 0;
}


static int on_read_processed(struct i2c_target_config *config, uint8_t *val)
{
	*val = buffer[count];
	count = (count + 1) % MSG_SIZE;
	return 0;
}


static int on_stop(struct i2c_target_config *config)
{
	count = 0;
	if (0 == strcmp(buffer, "RED"))
	{
		gpio_pin_set_dt(&red_led, 1);
		gpio_pin_set_dt(&green_led, 0);
		gpio_pin_set_dt(&blue_led, 0);

		strcpy(buffer, "done");
	}
	else if (0 == strcmp(buffer, "GREEN"))
	{
		gpio_pin_set_dt(&red_led, 0);
		gpio_pin_set_dt(&green_led, 1);
		gpio_pin_set_dt(&blue_led, 0);

		strcpy(buffer, "done");
	}
	else if (0 == strcmp(buffer, "BLUE"))
	{
		gpio_pin_set_dt(&red_led, 0);
		gpio_pin_set_dt(&green_led, 0);
		gpio_pin_set_dt(&blue_led, 1);

		strcpy(buffer, "done");
	}
	else if (0 == strcmp(buffer, "OFF"))
	{
		gpio_pin_set_dt(&red_led, 0);
		gpio_pin_set_dt(&green_led, 0);
		gpio_pin_set_dt(&blue_led, 0);

		strcpy(buffer, "done");
	}
	else
	{
		strcpy(buffer, "failed");
	}

	return 0;
}

int main(void)
{
	const struct device *i2c_dev = DEVICE_DT_GET(I2C_NODE);

	if (!device_is_ready(i2c_dev))
	{
		printk("I2C device not found!\n");
		exit(EXIT_FAILURE);
	}

	const struct i2c_target_callbacks callbacks = {
		.write_requested = on_write_requested,
		.read_requested = on_read_requested,
		.write_received = on_write_received,
		.read_processed = on_read_processed,
		.stop = on_stop,
	};

	struct i2c_target_config config = {
		.address = ADDRESS,
		.callbacks = &callbacks,
	};

	if (0 != i2c_target_register(i2c_dev, &config))
	{
		printk("I2C target register failed\n");
		exit(EXIT_FAILURE);
	}

	__ASSERT(gpio_is_ready_dt(&red_led), "Red LED GPIO not ready");
	__ASSERT(gpio_is_ready_dt(&green_led), "Green LED GPIO not ready");
	__ASSERT(gpio_is_ready_dt(&blue_led), "Blue LED GPIO not ready");

	__ASSERT(gpio_pin_configure_dt(&red_led, GPIO_OUTPUT_INACTIVE) == 0, "Failed to configure red LED");
	__ASSERT(gpio_pin_configure_dt(&green_led, GPIO_OUTPUT_INACTIVE) == 0, "Failed to configure green LED");
	__ASSERT(gpio_pin_configure_dt(&blue_led, GPIO_OUTPUT_INACTIVE) == 0, "Failed to configure blue LED");

	while (1)
	{
		k_msleep(1000);
	}

	return 0;
}
