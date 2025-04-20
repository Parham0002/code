#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>
#include <stdio.h>

#define LED_NODE DT_NODELABEL(gpio0) // We’re using GPIO port 0
#define LED_PIN 24					 // J2:17 on MCXN236 is P0_24

const struct device *gpio_dev = DEVICE_DT_GET(LED_NODE);

class Metro
{
private:
	uint64_t interval_ticks;
	uint64_t previous_tick;

public:
	Metro(uint32_t interval_ms)
	{
		interval_ticks = k_ms_to_ticks_ceil64(interval_ms);
		previous_tick = k_uptime_ticks();
	}

	bool check()
	{
		uint64_t now = k_uptime_ticks();
		if ((now - previous_tick) >= interval_ticks)
		{
			previous_tick = now;
			return true;
		}
		return false;
	}
};

int main(void)
{
	if (!device_is_ready(gpio_dev))
	{
		printk("GPIO device not ready\n");
		return -1;
	}

	// Configure the pin as output
	gpio_pin_configure(gpio_dev, LED_PIN, GPIO_OUTPUT_ACTIVE);

	Metro ledMetro(500);
	Metro printMetro(1000);

	bool led_is_on = false;

	while (1)
	{
		if (ledMetro.check())
		{
			led_is_on = !led_is_on;
			gpio_pin_set(gpio_dev, LED_PIN, led_is_on); // Direct pin toggle
		}

		if (printMetro.check())
		{
			printk("Hello world\n");
		}

		k_sleep(K_MSEC(10));
	}
	return 0;
}
