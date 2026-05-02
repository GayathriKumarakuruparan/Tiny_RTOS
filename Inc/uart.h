/*
 * uart.h
 *
 *  Created on: Apr 25, 2026
 *      Author: Netcom
 */

#ifndef UART_H_
#define UART_H_


#define 	SR_UART	(1U<<7)

void uart_init(void);
void setbaudrate(USART_TypeDef *UART,uint32_t FREQ, uint32_t BAUDRATE);
uint32_t calulationOfBaudrate(uint32_t FREQ, uint32_t BAUDRATE);
void uart_write(char ch);



#endif /* UART_H_ */
