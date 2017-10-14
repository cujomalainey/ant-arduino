#include "unity.h"

#ifdef UNIT_TEST

void setUp(void) {
// set stuff up here
}

void tearDown(void) {
// clean stuff up here
}

void test_function_calculator_addition2(void) {
    TEST_ASSERT_EQUAL(32, 25 + 7);
}

void test_function_calculator_subtraction2(void) {
    TEST_ASSERT_EQUAL(20, 23 - 3);
}

void test_function_calculator_multiplication2(void) {
    TEST_ASSERT_EQUAL(50, 25 * 2);
}

void test_function_calculator_division2(void) {
    TEST_ASSERT_EQUAL(32, 100 / 3);
}

int main(int argc, char **argv) {
    UNITY_BEGIN();
    RUN_TEST(test_function_calculator_addition2);
    RUN_TEST(test_function_calculator_subtraction2);
    RUN_TEST(test_function_calculator_multiplication2);
    UNITY_END();

    return 0;
}

#endif // UNIT_TEST