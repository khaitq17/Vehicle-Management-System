#ifndef __GPIO_H
#define	__GPIO_H

#include "stm32f10x.h"       

#define SDCARD_CS_PIN		GPIO_Pin_4
#define SDCARD_SCK_PIN	GPIO_Pin_5
#define SDCARD_MISO_PIN	GPIO_Pin_6
#define SDCARD_MOSI_PIN	GPIO_Pin_7
#define SDCARD_GPIO			GPIOA
#define SDCARD_GPIO_RCC	RCC_APB2Periph_GPIOA
#define TX_Pin 			GPIO_Pin_9
#define RX_Pin			GPIO_Pin_10
#define UART1_GPIO	GPIOA
void GPIO_Config(void);
void LED_Blink(uint8_t time);

#endif
