#include "stm32f10x.h" 
#include "GPIO.h"
#include "MFRC522.h"
#include "delay.h"
#include "SPI.h"
#include <stdio.h>
#include <string.h>

TM_MFRC522_Status_t status;
uint8_t CardID[5] = {0};
uint8_t str[MFRC522_MAX_LEN];
char buffer[64];
uint8_t isCardDetected = 0;

int main(void)
{	
	GPIO_Config();
	TIMER_Config();
	SPI_Config();
	TM_MFRC522_Init();
	
	while(1)
	{
		status = TM_MFRC522_Check(CardID);
		if (status == MI_OK && !isCardDetected)
    {
			GPIO_ResetBits(GPIOC, GPIO_Pin_13);
			isCardDetected = 1;
    } 
		else if (status != MI_OK && isCardDetected) 
		{
			GPIO_SetBits(GPIOC, GPIO_Pin_13);
			isCardDetected = 0;
		}
	}
}