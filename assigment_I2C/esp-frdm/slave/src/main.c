#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/i2c.h>
#include <zephyr/drivers/gpio.h>
#include <string.h>

#define MSG_SIZE 8
#define I2C_NODE DT_PROP(DT_PATH(zephyr_user), i2c)
#define ADDRESS DT_PROP(DT_PATH(zephyr_user), address)


#define RED_NODE DT_ALIAS(led0)
#define GREEN_NODE DT_ALIAS(led1)
#define BLUE_NODE DT_ALIAS(led2)

static const struct gpio_dt_spec red_led = GPIO_DT_SPEC_GET(RED_NODE, gpios);
static const struct gpio_dt_spec green_led = GPIO_DT_SPEC_GET(GREEN_NODE, gpios);
static const struct gpio_dt_spec blue_led = GPIO_DT_SPEC_GET(BLUE_NODE, gpios);

static uint8_t buffer[MSG_SIZE] = {0};
static int count = 0;

static void turn_off_all_leds(void)
{
	gpio_pin_set_dt(&red_led, 1);
	gpio_pin_set_dt(&green_led, 1);
	gpio_pin_set_dt(&blue_led, 1);
}


static void set_color(const char *color)
{
	turn_off_all_leds();

	if (strcmp(color, "red") == 0)
	{
		gpio_pin_set_dt(&red_led, 0);
	}
	else if (strcmp(color, "green") == 0)
	{
		gpio_pin_set_dt(&green_led, 0);
	}
	else if (strcmp(color, "blue") == 0)
	{
		gpio_pin_set_dt(&blue_led, 0);
	}
}

static int on_write_requested(struct i2c_target_config *config) { return 0; }

static int on_write_received(struct i2c_target_config *config, uint8_t val)
{
	if (val == '\n' || val == '\r')
	{
		buffer[count] = '\0'; 

		
		printk("Received command: %s\n", buffer);

		// First, always turn off LED
		turn_off_all_leds();

		// Check and apply command
		if (strcmp((char *)buffer, "red") == 0 ||
			strcmp((char *)buffer, "green") == 0 ||
			strcmp((char *)buffer, "blue") == 0)
		{
			set_color((char *)buffer); 
			strcpy((char *)buffer, "ok");
		}
		else if (strcmp((char *)buffer, "off") == 0)
		{
			strcpy((char *)buffer, "ok");
		}
		else
		{
			strcpy((char *)buffer, "fail");
		}

		count = 0; 
	}
	else if (count < MSG_SIZE - 1)
	{
		buffer[count++] = val;
	}

	return 0;
}

static int on_read_requested(struct i2c_target_config *config, uint8_t *val)
{
	*val = buffer[0];
	return 0;
}

static int on_read_processed(struct i2c_target_config *config, uint8_t *val)
{
	*val = buffer[++count];
	return 0;
}

static int on_stop(struct i2c_target_config *config) { return 0; }

int main(void)
{
	const struct device *i2c_dev = DEVICE_DT_GET(I2C_NODE);
	if (!device_is_ready(i2c_dev))
	{
		printk("I2C device not ready!\n");
		exit(EXIT_FAILURE);
	}

	gpio_pin_configure_dt(&red_led, GPIO_OUTPUT_INACTIVE);
	gpio_pin_configure_dt(&green_led, GPIO_OUTPUT_INACTIVE);
	gpio_pin_configure_dt(&blue_led, GPIO_OUTPUT_INACTIVE);
	turn_off_all_leds();

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

	if (i2c_target_register(i2c_dev, &config) != 0)
	{
		printk("I2C target register failed\n");
		exit(EXIT_FAILURE);
	}

	while (1)
	{
	}
	return 0;
}
