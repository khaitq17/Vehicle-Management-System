#include "SPI.h"


uint8_t SPI_Send(uint8_t data)
{
    SPI_I2S_SendData(SDCARD_SPI, data);

    while (SPI_I2S_GetFlagStatus(SDCARD_SPI, SPI_I2S_FLAG_BSY) == SET);

    return (uint8_t) SPI_I2S_ReceiveData(SDCARD_SPI);
}

void SPI_Config()
{
	RCC_APB2PeriphClockCmd(SDCARD_SPI_RCC, ENABLE);

	SPI_InitTypeDef SPI_InitStruct;
	
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
