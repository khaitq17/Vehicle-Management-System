#ifndef __GPIO_H
#define	__GPIO_H

#include "stm32f10x.h"       

#define MFRC522_CS_PIN		GPIO_Pin_12
#define MFRC522_SCK_PIN		GPIO_Pin_13
#define MFRC522_MISO_PIN	GPIO_Pin_14
#define MFRC522_MOSI_PIN	GPIO_Pin_15
#define MFRC522_GPIO			GPIOB
#define MFRC522_GPIO_RCC	RCC_APB2Periph_GPIOB


#define MFRC522_CS_LOW		GPIO_ResetBits(MFRC522_GPIO, MFRC522_CS_PIN)
#define MFRC522_CS_HIGH		GPIO_SetBits(MFRC522_GPIO, MFRC522_CS_PIN)

void GPIO_Config(void);
void MFRC522_InitPins(void);

#endif
