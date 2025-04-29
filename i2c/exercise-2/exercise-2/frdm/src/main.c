/**
 * @file main.c
 * @author Faroch Mehri (faroch.mehri@ya.se)
 * @brief An example of I2C in master mode.
 *        Look at: https://docs.zephyrproject.org/latest/hardware/peripherals/i2c.html
 *                 https://docs.zephyrproject.org/latest/doxygen/html/group__i2c__interface.html
 *                 https://docs.zephyrproject.org/latest/build/dts/intro-syntax-structure.html
 *
 * @version 0.1
 * @date 2025-02-09
 *
 * @copyright Copyright (c) 2025
 *
 */
#include <time.h>
#include <ctype.h>
#include <stdlib.h>
#include <zephyr/kernel.h>
#include <zephyr/drivers/rtc.h>
#include <zephyr/drivers/i2c.h>
#include <zephyr/console/console.h>

#define RTC_NODE DT_ALIAS(rtc)
#define I2C_NODE DT_NODELABEL(esp32c6)

static int read_command(void)
{
	int chr = EOF;

	while ((chr != 'S') && (chr != 'D') && (chr != '\n'))
	{
		chr = toupper(console_getchar());

		if (chr == '\r')
		{
			chr = '\n';
		}
	}

	console_putchar(chr);

	return chr;
}

int main(void)
{
	const struct device *rtc_dev = DEVICE_DT_GET(RTC_NODE);
	if (!device_is_ready(rtc_dev))
	{
		printk("The RTC device is not ready.\r\n");
		exit(EXIT_FAILURE);
	}

	const struct i2c_dt_spec i2c_dev = I2C_DT_SPEC_GET(I2C_NODE);
	if (!i2c_is_ready_dt(&i2c_dev))
	{
		printk("I2C device not found!");
		exit(EXIT_FAILURE);
	}

	if (0 != console_init())
	{
		printk("Failed to initialize console.\r\n");
		exit(EXIT_FAILURE);
	}

	char command;
	struct tm tminfo;
	struct rtc_time datetime = {0};

	while (1)
	{
		printf("S) Synchronize datetime\r\n"
			   "D) Display datetime\r\n"
			   "Enter a command: ");

		command = read_command();

		switch (command)
		{
		case 'S':
		{
			if (0 == i2c_write_dt(&i2c_dev, &command, sizeof(command)))
			{
				if (0 == i2c_read_dt(&i2c_dev, (uint8_t *)&tminfo, sizeof(tminfo)))
				{
					if (tminfo.tm_year > 0)
					{
						memcpy(&datetime, &tminfo, sizeof(tminfo));

						if (0 != rtc_set_time(rtc_dev, &datetime))
						{
							printk("Failed to set the RTC time!\r\n");
							exit(EXIT_FAILURE);
						}

						printk("\r\nSynchronized!\r\n\r\n");
					}
					else
					{
						printk("\r\nSynchronization failed!\r\n\r\n");
					}
				}
				else
				{
					printf("\r\nFailed to read\r\n");
				}
			}
			else
			{
				printf("\r\nFailed to write\r\n");
			}
		}
		break;

		case 'D':
		{
			if (0 != rtc_get_time(rtc_dev, &datetime))
			{
				printk("\r\nFailed to get the RTC time!\r\n");
				exit(EXIT_FAILURE);
			}
			else
			{
				printk("\r\n%04d-%02d-%02d %02d:%02d:%02d\r\n\r\n",
					   datetime.tm_year + 1900, datetime.tm_mon + 1, datetime.tm_mday,
					   datetime.tm_hour, datetime.tm_min, datetime.tm_sec);
			}
		}
		break;

		default:
			printf("\r\n");
			break;
		}
	}

	return EXIT_SUCCESS;
}
