#include <zephyr/kernel.h>
#include <zephyr/drivers/pwm.h>
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>
#include <stdio.h>

#define PWM_DEVICE_NAME DT_LABEL(DT_NODELABEL(pwm0)) // Adjust this to match your device tree
#define PWM_CHANNEL 0								 // PWM channel
#define PWM_PERIOD 1000000							 // PWM period in nanoseconds
#define FADE_STEP 10000								 // 1% fade step

// Initialize the PWM device
const struct device *pwm_dev = DEVICE_DT_GET(DT_NODELABEL(pwm0));

// Metro class for timed events (using k_uptime_ticks)
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
	if (!device_is_ready(pwm_dev))
	{
		printk("PWM device not ready\n");
		return;
	}

	printk("LED PWM fading started!\n");

	Metro fadeMetro(30);	// 30ms interval for PWM fade
	int pwm_duty_cycle = 0; // Start with 0% duty cycle (off)
	bool fade_in = true;	// Start fading in

	while (1)
	{
		if (fadeMetro.check())
		{
			if (fade_in)
			{
				pwm_duty_cycle += FADE_STEP;
				if (pwm_duty_cycle >= PWM_PERIOD)
				{
					pwm_duty_cycle = PWM_PERIOD;
					fade_in = false; // Start fading out
				}
			}
			else
			{
				pwm_duty_cycle -= FADE_STEP;
				if (pwm_duty_cycle <= 0)
				{
					pwm_duty_cycle = 0;
					fade_in = true; // Start fading in
				}
			}

			// Set the PWM duty cycle
			pwm_pin_set_usec(pwm_dev, PWM_CHANNEL, PWM_PERIOD, pwm_duty_cycle);
		}

		// Let other threads run and provide a small delay to avoid busy looping
		k_sleep(K_MSEC(10));
	}
	return 0;
}
