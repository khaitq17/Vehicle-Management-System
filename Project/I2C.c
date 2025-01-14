/***************************************************************************
 * @file    I2C.c
 * @brief   Define functions related to I2C
 * @details This file defines functions for I2C to use LCD module.
 * @version 1.0
 * @date    2024-10-22
 * @author  Tran Quang Khai
 ***************************************************************************/
#include "I2C.h"

/**************************************************************************
 * Define timeout to exit the loop 
 **************************************************************************/
#define I2C_TIMEOUT  0xFFFF

/**************************************************************************
 * @brief	Macro used for loops that will exit when a certain amount of time 
 *				has passed and the loop cannot complete execution and will be 
 *				declared an error
 * @param	Loop represents for flag status
 **************************************************************************/
#define Timed(x)     					\
	do { 												\
		Timeout = I2C_TIMEOUT; 		\
		while (x) { 							\
			if (Timeout-- == 0) {		\
				return Error;					\
			} 											\
		}													\
	} while(0)

/**************************************************************************
 * @brief   I2C_Config
 * @details This function configures I2C for LCD module.
 * @param   None
 * @return  void
 **************************************************************************/
void I2C_Config()
{
	RCC_APB1PeriphClockCmd(LCD_I2C_RCC, ENABLE);
	
  I2C_InitTypeDef I2C_InitStruct;

  I2C_InitStruct.I2C_ClockSpeed = 100000;
  I2C_InitStruct.I2C_Mode = I2C_Mode_I2C;
  I2C_InitStruct.I2C_DutyCycle = I2C_DutyCycle_2;
  I2C_InitStruct.I2C_OwnAddress1 = 0x00;
  I2C_InitStruct.I2C_Ack = I2C_Ack_Enable;
  I2C_InitStruct.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;

  I2C_Init(LCD_I2C, &I2C_InitStruct);
  I2C_Cmd(LCD_I2C, ENABLE);
}

/**************************************************************************
 * @brief   I2C_Write
 * @details This function writes data to a specific address.
 * @param   Address		Address to write data
 * @param   pData			Pointer to data to write
 * @param   length		Length of data
 * @return  Status		Return Error if write operation is failed
 *													 Success if write operation is successful
 **************************************************************************/
Status I2C_Write(uint8_t Address, const uint8_t *pData, uint8_t length)
{
  volatile uint32_t Timeout;
  Timed(I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY));

  I2C_GenerateSTART(I2C1, ENABLE);
  Timed(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));
  I2C_Send7bitAddress(I2C1, Address, I2C_Direction_Transmitter);
  Timed(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));

  while (length--) {
		I2C_SendData(I2C1, *pData++);
		Timed(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
  }

  I2C_GenerateSTOP(I2C1, ENABLE);
  return Success;
}

/**************************************************************************
 * @brief   I2C_Read
 * @details This function reads data from a specific address.
 * @param   Address		Address to read data
 * @param   pData			Pointer to data to read
 * @param   length		Length of data
 * @return  Status		Return Error if write operation is failed
 *													 Success if write operation is successful
 **************************************************************************/
Status I2C_Read(uint8_t Address, uint8_t *pData, uint8_t length)
{
  volatile uint32_t Timeout;
  Timed(I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY));

  I2C_GenerateSTART(I2C1, ENABLE);
  Timed(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));

  I2C_Send7bitAddress(I2C1, Address, I2C_Direction_Receiver);
  Timed(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));

  while (length--) {
		if (length == 0) I2C_AcknowledgeConfig(I2C1, DISABLE);

		Timed(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED));
    *pData++ = I2C_ReceiveData(I2C1);
  }

  I2C_GenerateSTOP(I2C1, ENABLE);
  I2C_AcknowledgeConfig(I2C1, ENABLE);
  return Success;
}

void I2C_Reset(I2C_TypeDef *I2Cx) {
    I2C_Cmd(I2Cx, DISABLE); // Disable I2C
    I2C_SoftwareResetCmd(I2Cx, ENABLE); // Reset I2C
    I2C_SoftwareResetCmd(I2Cx, DISABLE);
    I2C_Cmd(I2Cx, ENABLE); // Re-enable I2C
}
