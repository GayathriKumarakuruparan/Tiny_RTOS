/*
 * uart.c
 *
 *  Created on: Apr 25, 2026
 *      Author: Netcom
 */

#include<stm32f401xe.h>
#include<stdint.h>
#include"uart.h"

#define 	UART_ENR	(1U<<17)
#define 	PIN_A_CLK_EN	(1U<<0)
#define		SYS_FREQ		16000000
#define		BAUD_RATE		115200
#define 	UART_TX_EN		(1U<<3)
#define UART_ENABLE (1U<<13)

void uart_write(char ch){
	//CHECK WHTHER IT IS EMPTY
	//CHECK THE STATUS REGUSTER
	while(!(USART2->SR & SR_UART));
		//WRITE TO TRANSMIT DATA REGISTER
	USART2->DR = (ch & 0XFF);
}

void setbaudrate(USART_TypeDef *UART,uint32_t FREQ, uint32_t BAUDRATE){
	UART->BRR = calulationOfBaudrate(FREQ,BAUDRATE);
}
uint32_t calulationOfBaudrate(uint32_t FREQ, uint32_t BAUDRATE)
{
	return ((FREQ + (BAUDRATE/2))/BAUDRATE);
}

void uart_init(void)
{
	//Enable the Pin CLK of UART -> PA2
	RCC->AHB1ENR |= PIN_A_CLK_EN;
	//SET THE MODE OF PIN ->AF07
	GPIOA->MODER |= (1U<<5);
	GPIOA->MODER &= ~(1U<<4);

	//SET AF07 as UART TX
	GPIOA->AFR[0] &= ~(1U<<11);
	GPIOA->AFR[0] |= (1U<<10);
	GPIOA->AFR[0] |= (1U<<9);
	GPIOA->AFR[0] |= (1U<<8);
	//UART CLK ENABLE
	RCC->APB1ENR |= UART_ENR;
	//SET BAUDRATE
	setbaudrate(USART2,SYS_FREQ,BAUD_RATE);
	//ENABLE UART
	USART2->CR1 |= UART_ENABLE|UART_TX_EN;


}

