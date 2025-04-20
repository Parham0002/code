#include "fizzbuzz.h"
#include "unity.h" // Assuming you're using Unity for unit testing.

void test_regular_numbers(void)
{
    TEST_ASSERT_EQUAL_STRING("1", fizz_buzz(1));
    TEST_ASSERT_EQUAL_STRING("2", fizz_buzz(2));
    TEST_ASSERT_EQUAL_STRING("3", fizz_buzz(3)); // Fizz
    // Add more test cases here
}

void test_fizz_numbers(void)
{
    TEST_ASSERT_EQUAL_STRING("Fizz", fizz_buzz(3));
    TEST_ASSERT_EQUAL_STRING("Fizz", fizz_buzz(6));
    // Add more test cases for Fizz
}

void test_buzz_numbers(void)
{
    TEST_ASSERT_EQUAL_STRING("Buzz", fizz_buzz(5));
    TEST_ASSERT_EQUAL_STRING("Buzz", fizz_buzz(10));
    // Add more test cases for Buzz
}

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_regular_numbers);
    RUN_TEST(test_fizz_numbers);
    RUN_TEST(test_buzz_numbers);

    UNITY_END();

    return 0;
}
