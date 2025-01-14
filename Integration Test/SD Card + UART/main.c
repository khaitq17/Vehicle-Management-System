#include "stm32f10x.h"         
#include "GPIO.h"
#include "delay.h"
#include "SPI.h"
#include "ff.h"
#include "fatfs.h"
#include "fatfs_sd.h"
#include <stdio.h>
#include <string.h>


FATFS FatFs;  
FIL fil;    
UINT bw, br; 
FRESULT fr; 
char buffer[50];

void UART_Config(void);

int main(void)
{
	GPIO_Config();    
	SPI_Config();     
	TIMER_Config();   
	FATFS_Init();     
	UART_Config();
	
	fr = f_mount(&FatFs, "", 0); 
	if (fr == FR_OK) {
		printf("Mount file successfully\n");
	}
	
	fr = f_open(&fil, "Hello.txt", FA_READ);

	if (fr == FR_OK) {
		printf("Open and read file...\n");
		delay_ms(1000);
		f_read(&fil, buffer, sizeof(buffer) - 1, &br);
    buffer[br] = '\0'; 
		printf("%s\n", buffer);
    f_close(&fil);
  }
	/*
	if (fr == FR_OK) {
		fr = f_open(&fil, "Hello.txt", FA_WRITE | FA_CREATE_ALWAYS);	 
		if (fr == FR_OK) {
			f_write(&fil, "Tran Quang Khai", 15, &bw);	
			fr = f_close(&fil);							
			if (fr == FR_OK && bw == 15) {		 
				while (1) {
					LED_Blink(1);
				}
			}
		}
	}
	*/
	
	
		
		/*
fr = f_open(&fil, "Hello.txt", FA_CREATE_ALWAYS | FA_WRITE);
  if (fr == FR_OK) {
		f_truncate(&fil);
		f_close(&fil);
		LED_Blink(3);
  }	
	
		fr = f_open(&fil, "Hello.txt", FA_READ);
    if (fr == FR_OK) {
			f_read(&fil, buffer, sizeof(buffer) - 1, &br);
      buffer[br] = '\0';  
      f_close(&fil);
      if (br > 0) {
				while (1) {
					LED_Blink(1);
        }
      }
    }
	*/
  
	
	

	while(1) 
	{
		
	}
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

int fputc(int ch, FILE *f)
{
	while (!USART_GetFlagStatus(USART1, USART_FLAG_TXE));
	USART_SendData(USART1, (uint8_t)ch);
	while (!USART_GetFlagStatus(USART1, USART_FLAG_TC)){}
    
  return ch;
}