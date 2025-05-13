#include "unity.h"
#include "terminal.h"
#include <string.h>

static char output_buffer[1024];
static int output_index = 0;
static const char *fake_input = "1\n0\n";
static int input_index = 0;
int last_written_state = -1;

// Mocks
int bsp_console_getchar(void)
{
    return fake_input[input_index++];
}

bool bsp_console_print(const char *str)
{
    int len = strlen(str);
    if (output_index + len < sizeof(output_buffer))
    {
        memcpy(&output_buffer[output_index], str, len);
        output_index += len;
        output_buffer[output_index] = '\0';
        return true;
    }
    return false;
}

bool bsp_pin_write(int pin, int state)
{
    last_written_state = state;
    return true;
}

// Unity hooks
void setUp(void)
{
    output_index = 0;
    input_index = 0;
    last_written_state = -1;
}

void tearDown(void) {}

void test_terminal_run_should_toggle_led(void)
{
    terminal_run();

    TEST_ASSERT_EQUAL(0, last_written_state);
    TEST_ASSERT_NOT_NULL(strstr(output_buffer, "Enter a command"));
    TEST_ASSERT_NOT_NULL(strstr(output_buffer, "=> done"));
}

// 🔁 Required for ESP-IDF + Unity:
void app_main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_terminal_run_should_toggle_led);
    UNITY_END();
}
