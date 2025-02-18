/***************************************************************************
 * @file    SPI.c
 * @brief   Define functions related to SPI
 * @details This file defines functions for GPIO of RFID module, 
 *					SD card module.
 * @version 1.0
 * @date    2024-10-22
 * @author  Tran Quang Khai
 ***************************************************************************/
#include "SPI.h"

/**************************************************************************
 * @brief   SPI_Config
 * @details This function configures SPI for RFID module, SD card module.
 * @param   None
 * @return  void
 **************************************************************************/
void SPI_Config()
{
	SPI_InitTypeDef SPI_InitStruct;
	
	// SPI configure for MFRC522
	RCC_APB1PeriphClockCmd(MFRC522_SPI_RCC, ENABLE);

	SPI_InitStruct.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI_InitStruct.SPI_Mode = SPI_Mode_Master;
	SPI_InitStruct.SPI_DataSize = SPI_DataSize_8b;
	SPI_InitStruct.SPI_CPOL = SPI_CPOL_Low;
	SPI_InitStruct.SPI_CPHA = SPI_CPHA_1Edge;
	SPI_InitStruct.SPI_NSS = SPI_NSS_Soft;
	SPI_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_64;
	SPI_InitStruct.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_InitStruct.SPI_CRCPolynomial = 7;
	
	SPI_Init(MFRC522_SPI, &SPI_InitStruct);
	SPI_Cmd(MFRC522_SPI, ENABLE);
	
	// SPI configure for SD Card
	RCC_APB2PeriphClockCmd(SDCARD_SPI_RCC, ENABLE);
	
	SPI_InitStruct.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI_InitStruct.SPI_Mode = SPI_Mode_Master;
	SPI_InitStruct.SPI_DataSize = SPI_DataSize_8b;
	SPI_InitStruct.SPI_CPOL = SPI_CPOL_Low;
	SPI_InitStruct.SPI_CPHA = SPI_CPHA_1Edge;
	SPI_InitStruct.SPI_NSS = SPI_NSS_Soft;
	SPI_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_64;
	SPI_InitStruct.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_InitStruct.SPI_CRCPolynomial = 7;
	
	SPI_Init(SDCARD_SPI, &SPI_InitStruct);
	SPI_Cmd(SDCARD_SPI, ENABLE);
}

/**************************************************************************
 * @brief   MFRC522_SPI_Send
 * @details This function sends and receives data from SPI of RFID module.
 * @param   data	Data to send from SPI of RFID module
 * @return  uint8_t	Return data from SPI of RFID module
 **************************************************************************/
uint8_t MFRC522_SPI_Send(uint8_t data)
{
	SPI_I2S_SendData(MFRC522_SPI, data);
	
	while (SPI_I2S_GetFlagStatus(MFRC522_SPI, SPI_I2S_FLAG_BSY));
	
	return (uint8_t) SPI_I2S_ReceiveData(MFRC522_SPI);
}

/**************************************************************************
 * @brief   SDCard_SPI_Send
 * @details This function sends and receives data from SPI of SD card module.
 * @param   data	Data to send from SPI of SD card module
 * @return  uint8_t	Return data from SPI of SD card module
 **************************************************************************/
uint8_t SDCard_SPI_Send(uint8_t data)
{
  SPI_I2S_SendData(SDCARD_SPI, data);

  while (SPI_I2S_GetFlagStatus(SDCARD_SPI, SPI_I2S_FLAG_BSY));

  return (uint8_t) SPI_I2S_ReceiveData(SDCARD_SPI);
}