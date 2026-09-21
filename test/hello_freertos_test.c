#include <stdio.h>
#include <pico/stdlib.h>
#include <stdint.h>
#include <unity.h>
#include "unity_config.h"
#include "hello_fr_helpers.h"


void test_char(char c);

void setUp(void) {}

void tearDown(void) {}

void test_variable_assignment()
{
    int x = 1;
    TEST_ASSERT_TRUE_MESSAGE(x == 1,"Variable assignment failed.");
}

void test_multiplication(void)
{
    int x = 30;
    int y = 6;
    int z = x / y;
    TEST_ASSERT_TRUE_MESSAGE(z == 5, "Multiplication of two integers returned incorrect value.");
}

void test_char(char c){
    char actual = char_case_reverse(c);
    char expected = (c <= 'z' && c >= 'a') ? c-32 : c+32;
    TEST_ASSERT_EQUAL_CHAR_MESSAGE(actual, expected, "ERROR: actual result");
}

void test_char_case_logic()
{
    for (int i = 0; i <= 26; i++) {
        char t_char = 65 + i;
        test_char(t_char);
    }

    for (int i = 0; i <= 26; i++) {
        char t_char = 97 + i; // 97 (A)
        test_char(t_char);
    }
}

int main (void)
{
    stdio_init_all();
    while (1) {
        sleep_ms(5000); // Give time for TTY to attach.
        printf("Start tests\n");
        UNITY_BEGIN();
        RUN_TEST(test_variable_assignment);
        RUN_TEST(test_multiplication);
        RUN_TEST(test_char_case_logic);
        sleep_ms(5000);
        UNITY_END();
    }
}
