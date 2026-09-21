
#include "hello_fr_helpers.h"

char char_case_reverse(char c) {
    char ret_char;
    if (c <= 'z' && c >= 'a') ret_char = c - 32; // if the received char is lowercase, output the same value, sub 32 (uppercase)
    else if (c >= 'A' && c <= 'Z') ret_char = c + 32; // if received char (from somewehre) is uppercase, output same value + 32
    else ret_char = c;

    return ret_char;
}
