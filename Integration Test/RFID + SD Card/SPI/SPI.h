#ifndef __SPI_H
#define __SPI_H
#include "stm32f10x.h"
#include "GPIO.h"  

#define SDCARD_SPI				SPI1
#define SDCARD_SPI_RCC		RCC_APB2Periph_SPI1
#define MFRC522_SPI				SPI2								/* RFID SPI */
#define MFRC522_SPI_RCC		RCC_APB1Periph_SPI2	/* SPI RCC for RFID */

void SPI_Config(void);
uint8_t SPI_Send(uint8_t data);
uint8_t MFRC522_SPI_Send(uint8_t data);
#endif
