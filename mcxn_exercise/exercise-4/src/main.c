#include <stdlib.h>
#include <zephyr/kernel.h>
#include <zephyr/sys_clock.h>
#include <zephyr/drivers/pwm.h>
#include <zephyr/logging/log.h>
#include <zephyr/console/console.h>

LOG_MODULE_REGISTER(pwm_rgb, LOG_LEVEL_INF);

#define RED_PWM_NODE DT_NODELABEL(pwm_red)
#define RED_PWM_PERIOD DT_PWMS_PERIOD(RED_PWM_NODE)

#define GREEN_PWM_NODE DT_NODELABEL(pwm_green)
#define GREEN_PWM_PERIOD DT_PWMS_PERIOD(GREEN_PWM_NODE)

#define BLUE_PWM_NODE DT_NODELABEL(pwm_blue)
#define BLUE_PWM_PERIOD DT_PWMS_PERIOD(BLUE_PWM_NODE)

int main(void)
{
	const struct pwm_dt_spec red_led = PWM_DT_SPEC_GET(RED_PWM_NODE);
	if (!pwm_is_ready_dt(&red_led))
	{
		LOG_ERR("Error: didn't find %s device", DT_NODE_FULL_NAME(RED_PWM_NODE));
		exit(EXIT_FAILURE);
	}

	const struct pwm_dt_spec green_led = PWM_DT_SPEC_GET(GREEN_PWM_NODE);
	if (!pwm_is_ready_dt(&green_led))
	{
		LOG_ERR("Error: didn't find %s device", DT_NODE_FULL_NAME(GREEN_PWM_NODE));
		exit(EXIT_FAILURE);
	}

	const struct pwm_dt_spec blue_led = PWM_DT_SPEC_GET(BLUE_PWM_NODE);
	if (!pwm_is_ready_dt(&blue_led))
	{
		LOG_ERR("Error: didn't find %s device", DT_NODE_FULL_NAME(BLUE_PWM_NODE));
		exit(EXIT_FAILURE);
	}

	pwm_set_pulse_dt(&red_led, 0);
	pwm_set_pulse_dt(&green_led, 0);
	pwm_set_pulse_dt(&blue_led, 0);

	console_init();

	printk("Press any key to continue ...");
	(void)console_getchar();
	srand((uint32_t)k_uptime_ticks());

	int ret;
	uint32_t red_pulse_width, green_pulse_width, blue_pulse_width;

	while (1)
	{
		red_pulse_width = rand() % (RED_PWM_PERIOD + 1);
		green_pulse_width = rand() % (GREEN_PWM_PERIOD + 1);
		blue_pulse_width = rand() % (BLUE_PWM_PERIOD + 1);

		ret = pwm_set_pulse_dt(&red_led, red_pulse_width);
		if (ret != 0)
		{
			LOG_ERR("Failed to set red pulse width. Error code: %d", ret);
			exit(EXIT_FAILURE);
		}

		ret = pwm_set_pulse_dt(&green_led, green_pulse_width);
		if (ret != 0)
		{
			LOG_ERR("Failed to set green pulse width. Error code: %d", ret);
			exit(EXIT_FAILURE);
		}

		ret = pwm_set_pulse_dt(&blue_led, blue_pulse_width);
		if (ret != 0)
		{
			LOG_ERR("Failed to set blue pulse width. Error code: %d", ret);
			exit(EXIT_FAILURE);
		}

		printf("R = %08u, G = %08u, B = %08u\n", red_pulse_width, green_pulse_width, blue_pulse_width);

		k_sleep(K_MSEC(250));
	}

	return 0;
}