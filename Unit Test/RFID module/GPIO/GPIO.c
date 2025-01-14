#include "GPIO.h"

void GPIO_Config()
{
	// GPIO Configure for MFRC522
	RCC_APB2PeriphClockCmd(MFRC522_GPIO_RCC, ENABLE);
	GPIO_InitTypeDef GPIO_InitStruct;
	
	GPIO_InitStruct.GPIO_Pin = MFRC522_SCK_PIN | MFRC522_MOSI_PIN;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(MFRC522_GPIO, &GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Pin = MFRC522_MISO_PIN;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(MFRC522_GPIO, &GPIO_InitStruct);
	
	// GPIO Configure for LED
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStruct);
	GPIO_SetBits(GPIOC, GPIO_Pin_13);
}

void MFRC522_InitPins()
{
	RCC_APB2PeriphClockCmd(MFRC522_GPIO_RCC, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStruct;
	
	GPIO_InitStruct.GPIO_Pin = MFRC522_CS_PIN;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(MFRC522_GPIO, &GPIO_InitStruct);
	
	MFRC522_CS_HIGH;
}
