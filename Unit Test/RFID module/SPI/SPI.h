#ifndef __SPI_H
#define __SPI_H
#include "stm32f10x.h"
#include "GPIO.h"  

#define MFRC522_SPI				SPI2
#define MFRC522_SPI_RCC		RCC_APB1Periph_SPI2

void SPI_Config(void);
uint8_t SPI_Send(uint8_t data);

#endif
