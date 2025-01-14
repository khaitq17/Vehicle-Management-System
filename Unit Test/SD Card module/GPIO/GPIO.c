#include "GPIO.h"

void GPIO_Config()
{
	// GPIO Configure for SD Card
	RCC_APB2PeriphClockCmd(SDCARD_GPIO_RCC, ENABLE);
	GPIO_InitTypeDef GPIO_InitStruct;
	
	GPIO_InitStruct.GPIO_Pin = SDCARD_SCK_PIN | SDCARD_MOSI_PIN;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(SDCARD_GPIO, &GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Pin = SDCARD_MISO_PIN;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(SDCARD_GPIO, &GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Pin = SDCARD_CS_PIN;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(SDCARD_GPIO, &GPIO_InitStruct);
	GPIO_SetBits(SDCARD_GPIO, SDCARD_CS_PIN);
	
	// LED
	GPIO_InitTypeDef gpioInit;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	gpioInit.GPIO_Mode = GPIO_Mode_Out_PP;
	gpioInit.GPIO_Speed = GPIO_Speed_50MHz;
	gpioInit.GPIO_Pin = GPIO_Pin_13;
	GPIO_Init(GPIOC, &gpioInit);
	GPIO_SetBits(GPIOC, GPIO_Pin_13);
}

void LED_Blink(uint8_t time)
{
	for (int i = 0; i < time; i++) {
		GPIO_SetBits(GPIOC, GPIO_Pin_13);
		for (volatile int j = 0; j < 1000000; j++); 
		GPIO_ResetBits(GPIOC, GPIO_Pin_13);
		for (volatile int j = 0; j < 1000000; j++); 
  }
}
