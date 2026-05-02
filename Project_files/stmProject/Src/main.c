/**
 ******************************************************************************
 * @file           : main.c
 * @author         : GAYATHRI.k
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2026 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

#include "main.h"
#include "OSKernal.h"
#include"led.h"
#include"uart.h"
#include "mutex_queue.h"

volatile int tick_time;
mutex_t key;

void task0(void){

	while(1)
	{
		GPIOA->ODR ^= LED;
		tick_time=0;
		while(tick_time < 1600000)
		{
			tick_time++;
		}
	}


}

void task1(void){
    while(1){
    	mutex_lock(&key);
    	uart_write('g');
    	uart_write('a');
    	uart_write('y');
    	uart_write('a');
    	uart_write('t');
    	uart_write('h');
    	uart_write('r');
    	uart_write('i');
    	mutex_unlock(&key);
    	for(volatile int i=0;i<300000;i++);
    }
}

void task2(void){
	 while(1){
	    	mutex_lock(&key);
	    	uart_write('h');
	    	uart_write('a');
	    	uart_write('p');
	    	uart_write('p');
	    	uart_write('y');
	    	uart_write(' ');
	    	mutex_unlock(&key);
	    	for(volatile int i=0;i<300000;i++);
	    }
}

int main()
{
	led_init();
	mutex_init(&key);
	uart_init();
	OsKernal_init();
	osKernelAddThreads(&task0,&task1,&task2);
	OsKernalLaunch(QUANTA);
}
