#include "unity.h"
#include "utility.h"

// fakes setup
extern void set_fake_getchar_sequence(const char *input);
extern void set_fake_putchar_capture_buffer(char *buffer);
extern void use_linktime_fake();
extern void use_runtime_fake();
extern void use_preprocess_fake();
extern void use_compiletime_fake();

static char output_buffer[256];

void setUp(void)
{
    output_buffer[0] = '\0';
    use_linktime_fake();
}

void tearDown(void) {}

// tests:
void test_utility_string_read_should_read_string(void)
{
    set_fake_getchar_sequence("Hello\n");
    char buf[32];
    TEST_ASSERT_TRUE(utility_string_read(buf, sizeof(buf)));
    TEST_ASSERT_EQUAL_STRING("Hello", buf);
}

void test_utility_string_write_should_write_string(void)
{
    set_fake_putchar_capture_buffer(output_buffer);
    TEST_ASSERT_TRUE(utility_string_write("World"));
    TEST_ASSERT_EQUAL_STRING("World", output_buffer);
}

void test_utility_string_reverse_should_reverse_string(void)
{
    char str[] = "abcd";
    utility_string_reverse(str);
    TEST_ASSERT_EQUAL_STRING("dcba", str);
}

void test_utility_runtime_faking(void)
{
    use_runtime_fake();
    set_fake_getchar_sequence("Test\n");
    char buf[32];
    utility_string_read(buf, sizeof(buf));
    TEST_ASSERT_EQUAL_STRING("Test", buf);
}

void test_utility_preprocessor_faking(void)
{
    use_preprocess_fake();
    set_fake_getchar_sequence("Macro\n");
    char buf[32];
    utility_string_read(buf, sizeof(buf));
    TEST_ASSERT_EQUAL_STRING("Macro", buf);
}

void test_utility_compiletime_faking(void)
{
    use_compiletime_fake();
    set_fake_getchar_sequence("Build\n");
    char buf[32];
    utility_string_read(buf, sizeof(buf));
    TEST_ASSERT_EQUAL_STRING("Build", buf);
}

// The Unity test runner:
int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_utility_string_read_should_read_string);
    RUN_TEST(test_utility_string_write_should_write_string);
    RUN_TEST(test_utility_string_reverse_should_reverse_string);
    RUN_TEST(test_utility_runtime_faking);
    RUN_TEST(test_utility_preprocessor_faking);
    RUN_TEST(test_utility_compiletime_faking);
    return UNITY_END();
}
