/***************************************************************************
 * @file    I2C.h
 * @brief   Declare functions related to I2C
 * @details This file includes macros and functions for I2C to use LCD module.
 * @version 1.0
 * @date    2024-10-22
 * @author  Tran Quang Khai
 ***************************************************************************/
#ifndef __I2C_H
#define __I2C_H

#include "stm32f10x_i2c.h"

/**************************************************************************
 * Define I2C and RCC for LCD module
 **************************************************************************/
#define LCD_I2C				I2C1								/* LCD I2C */
#define LCD_I2C_RCC		RCC_APB1Periph_I2C1	/* I2C RCC for LCD */

/**************************************************************************
 * @enum 	Status
 * @brief	This type is used for I2C operation result
 **************************************************************************/
typedef enum {
    Error = 0,				/* Error */
    Success = !Error	/* Success */
} Status;

/**************************************************************************
 * @brief   I2C_Config
 * @param   None
 * @return  void
 **************************************************************************/
void I2C_Config();

/**************************************************************************
 * @brief   I2C_Write
 * @param   Address		Address to write data
 * @param   pData			Pointer to data to write
 * @param   length		Length of data
 * @return  Status		Return Error if write operation is failed
 *													 Success if write operation is successful
 **************************************************************************/
Status I2C_Write(uint8_t Address, const uint8_t *pData, uint8_t length);

/**************************************************************************
 * @brief   I2C_Read
 * @param   Address		Address to read data
 * @param   pData			Pointer to data to read
 * @param   length		Length of data
 * @return  Status		Return Error if write operation is failed
 *													 Success if write operation is successful
 **************************************************************************/
Status I2C_Read(uint8_t Address, uint8_t *pData, uint8_t length);

void I2C_Reset(I2C_TypeDef *I2Cx);
#endif /* __I2C_H */