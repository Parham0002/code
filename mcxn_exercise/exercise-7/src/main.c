#include <zephyr/kernel.h>
#include <zephyr/drivers/led.h>
#include <zephyr/drivers/adc.h>

#define RESISTANCE 4700.0f

int main(void)
{
	const struct led_dt_spec red_dev = LED_DT_SPEC_GET(DT_NODELABEL(red_led));
	const struct led_dt_spec green_dev = LED_DT_SPEC_GET(DT_NODELABEL(green_led));
	const struct led_dt_spec blue_dev = LED_DT_SPEC_GET(DT_NODELABEL(blue_led));
	const struct adc_dt_spec ldr_dev = ADC_DT_SPEC_GET(DT_PATH(zephyr_user));

	if (!led_is_ready_dt(&red_dev) || !led_is_ready_dt(&green_dev) || !led_is_ready_dt(&blue_dev))
	{
		printk("LED device is not ready");
		exit(EXIT_FAILURE);
	}

	if (!adc_is_ready_dt(&ldr_dev) || (0 > adc_channel_setup_dt(&ldr_dev)))
	{
		printk("LDR device is not ready");
		exit(EXIT_FAILURE);
	}

	int16_t value;
	struct adc_sequence sequence = {
		.buffer = &value,
		.buffer_size = sizeof(value),
		.calibrate = true,
	};

	int32_t millivolts, resistance;

	while (1)
	{
		if ((0 != adc_sequence_init_dt(&ldr_dev, &sequence)) || (0 != adc_read_dt(&ldr_dev, &sequence)))
		{
			printk("ADC failed to read\n");
			exit(EXIT_FAILURE);
		}

		millivolts = value;
		if (0 > adc_raw_to_millivolts_dt(&ldr_dev, &millivolts))
		{
			printk("ADC failed to convert the raw value to millivolts\n");
			exit(EXIT_FAILURE);
		}

		// I = (ldr_dev.vref_mv - millivolts) / RESISTANCE and then R = millivolts / I
		resistance = (RESISTANCE * millivolts) / (ldr_dev.vref_mv - millivolts);

		if (resistance < 2000)
		{
			if ((0 != led_off_dt(&red_dev)) || (0 != led_off_dt(&green_dev)) || (0 != led_on_dt(&blue_dev)))
			{
				printk("Failed to turn the blue LED on\n");
				exit(EXIT_FAILURE);
			}
		}
		else if (resistance < 5000)
		{
			if ((0 != led_off_dt(&red_dev)) || (0 != led_on_dt(&green_dev)) || (0 != led_off_dt(&blue_dev)))
			{
				printk("Failed to turn the green LED on\n");
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			if ((0 != led_on_dt(&red_dev)) || (0 != led_off_dt(&green_dev)) || (0 != led_off_dt(&blue_dev)))
			{
				printk("Failed to turn the red LED on\n");
				exit(EXIT_FAILURE);
			}
		}
	}

	return EXIT_SUCCESS;
}
