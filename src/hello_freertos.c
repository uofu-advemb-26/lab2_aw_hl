/**
 * Copyright (c) 2022 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>

#include "FreeRTOS.h"
#include "task.h"

#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "pico/cyw43_arch.h"

// states
int count = 0; 
bool on = false;

// priority of main task is 1 above the idle task priority?
#define MAIN_TASK_PRIORITY      ( tskIDLE_PRIORITY + 1UL )
#define BLINK_TASK_PRIORITY     ( tskIDLE_PRIORITY + 2UL )
#define MAIN_TASK_STACK_SIZE configMINIMAL_STACK_SIZE
#define BLINK_TASK_STACK_SIZE configMINIMAL_STACK_SIZE

// blink task does not use any params
void blink_task(__unused void *params) {
    // hardware call? 
    // i assume this is a like a test call to verify that the arch init is equal to the pico ok value. 
    hard_assert(cyw43_arch_init() == PICO_OK);

    // no return statment
    while (true) {
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, on); // architecture call t turn led to on value
        if (count++ % 11) on = !on; // toggle on if count is divisible by 11 ? and increment count!
        vTaskDelay(250);    // pause task
    }
}


void main_task(__unused void *params) {
    // main task runs subthreads with the priority and stuff
    xTaskCreate(blink_task, "BlinkThread",
                BLINK_TASK_STACK_SIZE, NULL, BLINK_TASK_PRIORITY, NULL);
    char c;
    while(c = getchar()) { // get char is hardware call from picosdk i think
        if (c <= 'z' && c >= 'a') putchar(c - 32); // if the received char is lowercase, output the same value, sub 32 (uppercase)
        else if (c >= 'A' && c <= 'Z') putchar(c + 32); // if received char (from somewehre) is uppercase, output same value + 32
        else putchar(c);
    }
}

int main( void ) // on boot, execution starts here
{
    // setup stuff
    stdio_init_all(); 
    const char *rtos_name;
    rtos_name = "FreeRTOS";
    TaskHandle_t task;


    // create the main thread 
    xTaskCreate(main_task, "MainThread",
                MAIN_TASK_STACK_SIZE, NULL, MAIN_TASK_PRIORITY, &task);

    // this is what starts the sub threads
    vTaskStartScheduler(); 
    return 0;

}
