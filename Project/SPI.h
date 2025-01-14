/***************************************************************************
 * @file    SPI.h
 * @brief   Declare functions related to SPI
 * @details This file includes macros and functions for SPI of RFID module, 
 *					SD card module.
 * @version 1.0
 * @date    2024-10-22
 * @author  Tran Quang Khai
 ***************************************************************************/
#ifndef __SPI_H
#define __SPI_H

#include "stm32f10x_spi.h"              

/**************************************************************************
 * Define SPI and RCC for RFID module
 **************************************************************************/
#define MFRC522_SPI				SPI2								/* RFID SPI */
#define MFRC522_SPI_RCC		RCC_APB1Periph_SPI2	/* SPI RCC for RFID */

/**************************************************************************
 * Define SPI and RCC for SD card
 **************************************************************************/
#define SDCARD_SPI				SPI1								/* SD Card SPI */
#define SDCARD_SPI_RCC		RCC_APB2Periph_SPI1	/* SPI RCC for SD Card */

/**************************************************************************
 * @brief   SPI_Config
 * @param   none
 * @return  void
 **************************************************************************/
void SPI_Config(void);

/**************************************************************************
 * @brief   MFRC522_SPI_Send
 * @param   data		Data to send from SPI of RFID module
 * @return  uint8_t	Return data from SPI of RFID module
 **************************************************************************/
uint8_t MFRC522_SPI_Send(uint8_t data);

/**************************************************************************
 * @brief   SDCard_SPI_Send
 * @param   data		Data to send from SPI of SD card module
 * @return  uint8_t	Return data from SPI of SD card module
 **************************************************************************/
uint8_t SDCard_SPI_Send(uint8_t data);

#endif /* __SPI_H */