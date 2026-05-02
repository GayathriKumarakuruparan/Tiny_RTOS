/*
 * led.c
 *
 *  Created on: Apr 23, 2026
 *      Author: Netcom
 */
#include<stm32f401xe.h>
#include"led.h"

void led_init(void)
{
	//ENABLE THE CLOCK OF PIN PA5
	RCC->AHB1ENR |= CLK_ENABLE;
	//ENABLE THE DIRECTION MODE OF GPIO PIN
	GPIOA->MODER |= (1U<<10);
	GPIOA->MODER &= ~(1U<<11);



}
