#include "stm32f10x.h"            
#include "stm32f10x_usart.h"          
#include "delay.h"
#include <stdio.h>
#include <string.h>

#define TX_Pin 			GPIO_Pin_9
#define RX_Pin			GPIO_Pin_10
#define UART1_GPIO	GPIOA

void RCC_Config(void);
void GPIO_Config(void);
void UART_Config(void);
void UART_SendChar(char c);
char UART_ReceiveChar();
void UART_SendString(char* str);

int main(void)
{
	RCC_Config();
	GPIO_Config();
	UART_Config();
	
	printf("Unit Testing...\n");
	for (int i = 0; i < 1000000000; i++);
	printf("Hello World!\n");
		for (int i = 0; i < 1000000000; i++);

	printf("My name is Tran Quang Khai\n");
		for (int i = 0; i < 1000000000; i++);

	for (uint8_t i = 0; i < 20; i++)
	{
		printf("%d\n", i);
			for (int i = 0; i < 10000000; i++);

	}
	
	while(1)
	{	
		
	}
}

void RCC_Config(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_USART1, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
}

void GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	GPIO_InitStruct.GPIO_Pin = TX_Pin;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(UART1_GPIO, &GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Pin = RX_Pin;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(UART1_GPIO, &GPIO_InitStruct);
}

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
void UART_SendChar(char c)
{
	USART_SendData(USART1, c);
	while(!USART_GetFlagStatus(USART1, USART_FLAG_TXE));
}
char UART_ReceiveChar()
{
	while(!USART_GetFlagStatus(USART1, USART_FLAG_RXNE));
	return (uint8_t) USART_ReceiveData(USART1);
}
void UART_SendString(char* str)
{
	while (*str)
	{
		USART_SendData(USART1, *str);
		while (!USART_GetFlagStatus(USART1, USART_FLAG_TXE));
		str++;
	}
}

int fputc(int ch, FILE *f)
{
	while (!USART_GetFlagStatus(USART1, USART_FLAG_TXE));
	USART_SendData(USART1, (uint8_t)ch);
	while (!USART_GetFlagStatus(USART1, USART_FLAG_TC)){}
    
  return ch;
}

