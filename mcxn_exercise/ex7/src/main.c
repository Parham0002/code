#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/adc.h>
#include <zephyr/sys/printk.h>

/* Get references to the LEDs from the board DTS */
#define RED_LED_NODE DT_ALIAS(red_led)
#define GREEN_LED_NODE DT_ALIAS(green_led)
#define BLUE_LED_NODE DT_ALIAS(blue_led)

/* Check if all LEDs are properly defined */
#if !(DT_NODE_HAS_STATUS(RED_LED_NODE, okay) &&   \
	  DT_NODE_HAS_STATUS(GREEN_LED_NODE, okay) && \
	  DT_NODE_HAS_STATUS(BLUE_LED_NODE, okay))
#error "Unsupported board: LED aliases are not defined correctly"
#endif

/* ADC configuration */
#define ADC_NODE DT_NODELABEL(lpadc0)
#define ADC_CHANNEL 6	  // Assuming your LDR is connected to P4_6
#define ADC_RESOLUTION 12 // 12 bits ADC resolution
#define ADC_GAIN ADC_GAIN_1
#define ADC_REFERENCE ADC_REF_INTERNAL
#define ADC_ACQUISITION_TIME ADC_ACQ_TIME_DEFAULT

/* ADC reading buffer */
static uint16_t adc_sample_buffer;

/* LED device structures */
static const struct gpio_dt_spec red_led = GPIO_DT_SPEC_GET(RED_LED_NODE, gpios);
static const struct gpio_dt_spec green_led = GPIO_DT_SPEC_GET(GREEN_LED_NODE, gpios);
static const struct gpio_dt_spec blue_led = GPIO_DT_SPEC_GET(BLUE_LED_NODE, gpios);

/* ADC channel setup */
static const struct adc_channel_cfg adc_channel_cfg = {
	.gain = ADC_GAIN,
	.reference = ADC_REFERENCE,
	.acquisition_time = ADC_ACQUISITION_TIME,
	.channel_id = ADC_CHANNEL,
	.differential = 0,
};

int main(void)
{
	const struct device *adc_dev = DEVICE_DT_GET(ADC_NODE);

	if (!device_is_ready(adc_dev))
	{
		printk("ADC device not ready!\n");
		exit(1);
	}

	if (!device_is_ready(red_led.port) || !device_is_ready(green_led.port) || !device_is_ready(blue_led.port))
	{
		printk("LED device not ready!\n");
		exit(1);
	}

	/* Configure LEDs */
	gpio_pin_configure_dt(&red_led, GPIO_OUTPUT_INACTIVE);
	gpio_pin_configure_dt(&green_led, GPIO_OUTPUT_INACTIVE);
	gpio_pin_configure_dt(&blue_led, GPIO_OUTPUT_INACTIVE);

	/* Configure ADC channel */
	int ret = adc_channel_setup(adc_dev, &adc_channel_cfg);
	if (ret != 0)
	{
		printk("ADC channel setup failed: %d\n", ret);
		exit(1);
	}

	struct adc_sequence sequence = {
		.channels = BIT(ADC_CHANNEL),
		.buffer = &adc_sample_buffer,
		.buffer_size = sizeof(adc_sample_buffer),
		.resolution = ADC_RESOLUTION,
	};

	while (1)
	{
		ret = adc_read(adc_dev, &sequence);
		if (ret != 0)
		{
			printk("ADC read error: %d\n", ret);
			continue;
		}

		uint16_t adc_value = adc_sample_buffer;
		printk("ADC Value: %d\n", adc_value);

		/* Approximate voltage range calculation if needed */

		/* Simple threshold logic */
		if (adc_value < 1000)
		{ // Assume < 2kΩ LDR means < 1000 ADC counts (example)
			gpio_pin_set_dt(&blue_led, 1);
			gpio_pin_set_dt(&green_led, 0);
			gpio_pin_set_dt(&red_led, 0);
		}
		else if (adc_value < 2500)
		{ // Between 2kΩ and 5kΩ
			gpio_pin_set_dt(&blue_led, 0);
			gpio_pin_set_dt(&green_led, 1);
			gpio_pin_set_dt(&red_led, 0);
		}
		else
		{ // >5kΩ
			gpio_pin_set_dt(&blue_led, 0);
			gpio_pin_set_dt(&green_led, 0);
			gpio_pin_set_dt(&red_led, 1);
		}

		k_sleep(K_MSEC(500));
	}
	return 1;
}