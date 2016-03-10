/**
 * @file usart.h
 * Contains declarations for USART1 functions.
 * @author Ivan Pavic
 */
#ifndef _USART_H_
#define _USART_H_

#include <stm32f4xx_usart.h>
#include <stm32f4xx_gpio.h>

void init_USART1(int baudrate);
void USART_puts(USART_TypeDef* USARTx, char* bytes);

#endif
