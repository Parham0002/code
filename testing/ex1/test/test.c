#include <unity.h>
#include "main.h"

/**
 * @brief This function is called before running every test function to initialize the environment for the test.
 *        For example if the module needs initialization or to start, we can do it in this function,
 *        or reseting the required variables for the test.
 */
void setUp(void){}

/**
 * @brief This function is called after running every test function to cleanup the environment.
 *        For example if the module needs to free memory, to be stoped, or etc. we can do it in this function
 */
void tearDown(void){}

void test_fizzbuzz(void){
    TEST_ASSERT_EQUAL_STRING("FizzBuzz", fizzbuzz(15));
}