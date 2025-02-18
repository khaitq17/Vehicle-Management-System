/***************************************************************************
 * @file    UART.c
 * @brief   Define functions related to UART
 * @details This file defines functions for UART to debug.
 * @version 1.0
 * @date    2024-10-22
 * @author  Tran Quang Khai
 ***************************************************************************/
#include "UART.h"

/**************************************************************************
 * @brief   UART_Config
 * @details This function configures UART to debug.
 * @param   none
 * @return  void
 **************************************************************************/
void UART_Config()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

	USART_InitTypeDef UART_InitStruct;
	
	UART_InitStruct.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	UART_InitStruct.USART_BaudRate = 9600;
	UART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	UART_InitStruct.USART_WordLength = USART_WordLength_8b;
	UART_InitStruct.USART_StopBits = USART_StopBits_1;
	UART_InitStruct.USART_Parity = USART_Parity_No;
	
	USART_Init(USART1, &UART_InitStruct);
	USART_Cmd(USART1, ENABLE);
}

/**************************************************************************
 * @brief   UART_SendChar
 * @details This function sends a character from UART1.
 * @param   c		Character that sent by UART1
 * @return  void
 **************************************************************************/
void UART_SendChar(char c)
{
	USART_SendData(USART1, c);
	while(!USART_GetFlagStatus(USART1, USART_FLAG_TXE));
}

/**************************************************************************
 * @brief   UART_ReceiveChar
 * @details This function receives a character from UART1.
 * @param   none
 * @return  char	A character that received from UART1
 **************************************************************************/
char UART_ReceiveChar()
{
	while(!USART_GetFlagStatus(USART1, USART_FLAG_RXNE));
	return (uint8_t) USART_ReceiveData(USART1);
}

/**************************************************************************
 * @brief   UART_SendString
 * @details This function sends a string from UART1.
 * @param   str		Pointer to first character of a string
 * @return  void
 **************************************************************************/
void UART_SendString(char* str)
{
	while (*str)
	{
		USART_SendData(USART1, *str);
		while (!USART_GetFlagStatus(USART1, USART_FLAG_TXE));
		str++;
	}
}