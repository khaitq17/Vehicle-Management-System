#ifndef __SPI_H
#define __SPI_H
#include "stm32f10x.h"
#include "GPIO.h"  

#define SDCARD_SPI				SPI1
#define SDCARD_SPI_RCC		RCC_APB2Periph_SPI1

void SPI_Config(void);
uint8_t SPI_Send(uint8_t data);

#endif
