#include "stm32f10x.h" 
#include "GPIO.h"
#include "MFRC522.h"
#include "delay.h"
#include "UART.h"
#include "SPI.h"
#include <stdio.h>
#include <string.h>

TM_MFRC522_Status_t status;
uint8_t CardID[5];
uint8_t str[MFRC522_MAX_LEN];
char buffer[64];

int main(void)
{	
	GPIO_Config();
	UART_Config();
	TIMER_Config();
	SPI_Config();
	TM_MFRC522_Init();
	
	printf("Welcome to RFID module\n");
	delay_ms(1000);
	
	while(1)
	{
		status = TM_MFRC522_Check(CardID);
		if (status == MI_OK)
    {
			printf("Card detected!\n");
      printf("UID: %02X %02X %02X %02X %02X\n", CardID[0], CardID[1], CardID[2], CardID[3], CardID[4]);
			delay_ms(1000);
    }
	}
}


int fputc(int ch, FILE *f)
{
	while (!USART_GetFlagStatus(USART1, USART_FLAG_TXE));
	USART_SendData(USART1, (uint8_t)ch);
	while (!USART_GetFlagStatus(USART1, USART_FLAG_TC)){}
    
  return ch;
}

