
#include "hello_fr_helpers.h"
#include <stdio.h>
#include <stdbool.h>

#include "FreeRTOS.h"
#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "pico/cyw43_arch.h"
#include "task.h"

char char_case_reverse(char c) {
    char ret_char;
    if (c <= 'z' && c >= 'a') ret_char = c - 32; // if the received char is lowercase, output the same value, sub 32 (uppercase)
    else if (c >= 'A' && c <= 'Z') ret_char = c + 32; // if received char (from somewehre) is uppercase, output same value + 32
    else ret_char = c;

    return ret_char;
}



bool toggle_led(int count, bool on){
    if (count % 11) 
        on = !on;
    return on;
}


bool handle_led(int* pcount, bool on){
    bool new_on = toggle_led(*pcount, on); // toggle on if count is divisible by 11 ? and increment count!
    (*pcount)++;
    return new_on;
}
