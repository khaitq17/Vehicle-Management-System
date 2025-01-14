#include "UART.h"

void UART_Config(void)
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


void UART_SendChar(USART_TypeDef* USARTx, char data)
{
	USART_SendData(USARTx, data);
	while(!USART_GetFlagStatus(USARTx, USART_FLAG_TXE));
}


char UART_ReceiveChar(USART_TypeDef* USARTx)
{
	while(!USART_GetFlagStatus(USARTx, USART_FLAG_RXNE));
	return (uint8_t) USART_ReceiveData(USARTx);
}


void UART_SendString(USART_TypeDef* USARTx, char* str)
{
	while (*str)
	{
		USART_SendData(USARTx, *str);
		while (!USART_GetFlagStatus(USARTx, USART_FLAG_TXE));
		str++;
	}
}

