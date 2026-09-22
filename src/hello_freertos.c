/**
 * Copyright (c) 2022 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>

#include "FreeRTOS.h"
#include "task.h"
#include "hello_fr_helpers.h"

#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "pico/cyw43_arch.h"

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

    int count = 0;
    bool on = false;
    // no return statment
    while (true) {
        handle_led(&count, on);
        vTaskDelay(250);    // pause task
    }
}

void process_char(void){
    char c = getchar();
    putchar(char_case_reverse(c));
}



void main_task(__unused void *params) {
    // main task runs subthreads with the priority and stuff
    xTaskCreate(blink_task, "BlinkThread",
                BLINK_TASK_STACK_SIZE, NULL, BLINK_TASK_PRIORITY, NULL);

    while(true) { // get char is hardware call from picosdk i think
        process_char();
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
