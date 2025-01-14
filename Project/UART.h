/***************************************************************************
 * @file    UART.h
 * @brief   Declare functions related to UART
 * @details This file includes functions for UART to debug.
 * @version 1.0
 * @date    2024-10-22
 * @author  Tran Quang Khai
 ***************************************************************************/
#ifndef __UART_H
#define __UART_H

#include "stm32f10x_usart.h"          

// Use USART1 to debug

/**************************************************************************
 * @brief   UART_Config
 * @param   none
 * @return  void
 **************************************************************************/
void UART_Config(void);

/**************************************************************************
 * @brief   UART_SendChar
 * @param   c			Character that sent by UART1
 * @return  void
 **************************************************************************/
void UART_SendChar(char c);

/**************************************************************************
 * @brief   UART_ReceiveChar
 * @param   none
 * @return  char	A character that received from UART1
 **************************************************************************/
char UART_ReceiveChar();

/**************************************************************************
 * @brief   UART_SendString
 * @param   str		Pointer to first character of a string
 * @return  void
 **************************************************************************/
void UART_SendString(char* str);

#endif /* __UART_H */