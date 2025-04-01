/**
 * @file main.c
 * @author Faroch Mehri (faroch.mehri@ya.se)
 * @brief An example of using an ADC channel(LPADC0_A3) to read temperature using TMP36 sensor
 *        Look at: https://docs.zephyrproject.org/latest/doxygen/html/group__adc__interface.html
 *
 *        Connections:
 *           TMP36 .... FRDM_MCXN236
 *             Vs --------> VDDA
 *            GND --------> GND
 *            Vout -------> J4:2(P4_6)
 *
 * @version 0.1
 * @date 2025-03-29
 *
 * @copyright Copyright (c) 2025
 *
 */
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/drivers/adc.h>

LOG_MODULE_REGISTER(tmp36);

#define MILLIVOLT_OFFSET 500.0
#define MILLIVOLT_PER_CELSIUS 10

#define ADC_CHANNEL 3 /* ARD_A0, P4_6, ADC0_A3 */
#define ADC_RESOLUTION 12
#define ADC_GAIN ADC_GAIN_1						  /* Gain is a factor by which the input analog signal is amplified \
													 before being converted to a digital value. */
#define ADC_REFERENCE_VOLTAGE 1800				  /* VREF volatge is 1800 mv */
#define ADC_NODE DT_NODELABEL(lpadc0)			  /* ADC node in the device tree */
#define ADC_REFERENCE ADC_REF_EXTERNAL1			  /* External reference voltage */
#define ADC_ACQUISITION_TIME ADC_ACQ_TIME_DEFAULT /* Acquisition time (sampling time) is the time required for the       \
													 Analog-to-Digital Converter (ADC) to capture the input voltage      \
													 during sampling. The acquisition time of a Successive Approximation \
													 Register (SAR) ADC is the amount of time required to charge the     \
													 holding capacitor (CHOLD) on the front end of an ADC */

int main(void)
{
	const struct device *adc_dev = DEVICE_DT_GET(ADC_NODE);

	if (!device_is_ready(adc_dev))
	{
		LOG_ERR("ADC device is not ready");
		return EXIT_FAILURE;
	}

	struct adc_channel_cfg channel_cfg = {
		.gain = ADC_GAIN,
		.reference = ADC_REFERENCE,
		.acquisition_time = ADC_ACQUISITION_TIME,
		.channel_id = ADC_CHANNEL,
		.input_positive = ADC_CHANNEL,
	};

	if (0 != adc_channel_setup(adc_dev, &channel_cfg))
	{
		LOG_ERR("ADC device Could not setup channel %d", ADC_CHANNEL);
		return EXIT_FAILURE;
	}

	int32_t millivolts = 0;
	struct adc_sequence sequence = {
		.channels = BIT(ADC_CHANNEL),
		.buffer = &millivolts,
		.buffer_size = sizeof(millivolts),
		.resolution = ADC_RESOLUTION,
		.oversampling = 4,
		.calibrate = true,
	};

	while (1)
	{
		if (0 != adc_read(adc_dev, &sequence))
		{
			LOG_ERR("ADC failed to read\n");
			return EXIT_FAILURE;
		}

		if (0 != adc_raw_to_millivolts(ADC_REFERENCE_VOLTAGE, ADC_GAIN, ADC_RESOLUTION, &millivolts))
		{
			LOG_ERR("ADC failed to convert the raw value to millivolts\n");
			return EXIT_FAILURE;
		}

		printf("Temperature = %0.1f\n", (millivolts - MILLIVOLT_OFFSET) / MILLIVOLT_PER_CELSIUS);

		k_sleep(K_MSEC(500));
	}

	return EXIT_SUCCESS;
}
