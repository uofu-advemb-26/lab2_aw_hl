#include <stdio.h>
#include <pico/stdlib.h>
#include <stdint.h>
#include <unity.h>
#include <stdbool.h>
#include "unity_config.h"
#include "hello_fr_helpers.h"

#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "pico/cyw43_arch.h"


void test_char(char c);

void setUp(void) {}

void tearDown(void) {


}

void test_variable_assignment(void)
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
    // printf("Expected: %c\n", expected);
    // printf("Actual: %c\n", actual);
    TEST_ASSERT_EQUAL_CHAR_MESSAGE(expected, actual, "ERROR: actual result");
}

void test_non_letter_char(char c) {
    char actual = char_case_reverse(c);
    char expected = c;
    TEST_ASSERT_EQUAL_CHAR_MESSAGE(expected, actual, "ERROR: expected result differes from actual result for normal non letter char");

}

void test_char_case_logic()
{
    for (int i = 0; i < 26; i++) {
        char t_char = 65 + i;
        test_char(t_char);
    }

    for (int i = 0; i < 26; i++) {
        char t_char = 97 + i; // 97 (A)
        test_char(t_char);
    }

    for (int i = 33; i < 65; i++) {
        test_non_letter_char((char) i);
    }
}

void test_light_switch_should_toggle()
{
    bool on;
    int test_count = 11;
    bool pre_toggle = on; 

    on = toggle_led(test_count);  // with test count == 11, on should not toggle
    TEST_ASSERT_EQUAL_CHAR_MESSAGE(pre_toggle, on, "ERROR: expected led on status diffeered from actual. LED Toggled when it shouldnt have");
}

void test_light_switch_dont_toggle(void){

    int test_count = 12;
    bool on;
    bool pre_toggle = on;

    on = toggle_led(test_count);
    TEST_ASSERT_NOT_EQUAL_CHAR_MESSAGE(pre_toggle, on, "ERROR: expected led on status diffeered from actual. LED did not toggle when it should have");
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
        RUN_TEST(test_light_switch_should_toggle);
        RUN_TEST(test_light_switch_dont_toggle);
        sleep_ms(5000);
        UNITY_END();
    }
}
