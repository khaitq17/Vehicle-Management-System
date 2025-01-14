#ifndef __UART_H
#define __UART_H

#include "stm32f10x.h"        
#include "stm32f10x_usart.h"           

void UART_Config(void);
void UART_SendChar(USART_TypeDef* USARTx, char data);
char UART_ReceiveChar(USART_TypeDef* USARTx);
void UART_SendString(USART_TypeDef* USARTx, char* str);

#endif
