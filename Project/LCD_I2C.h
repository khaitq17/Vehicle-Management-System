/***************************************************************************
 * @file    LCD_I2C.h
 * @brief   Declare functions related to LCD module
 * @details This file includes macros and functions to use LCD module.
 * @version 1.0
 * @date    2024-10-22
 ***************************************************************************/
#ifndef __LCD_I2C_H
#define __LCD_I2C_H

#include "I2C.h"
#include "TIM.h"

/**************************************************************************
 * LCD module address
 **************************************************************************/
#define I2C_LCD_ADDR 0x4E

/**************************************************************************
 * Delay milliseconds for LCD
 **************************************************************************/
#define I2C_LCD_Delay_Ms(u16DelayMs) delay_ms(u16DelayMs)

/**************************************************************************
 * Register
 **************************************************************************/
#define LCD_EN 2
#define LCD_RW 1
#define LCD_RS 0
#define LCD_D4 4
#define LCD_D5 5
#define LCD_D6 6
#define LCD_D7 7
#define LCD_BL 3

/**************************************************************************
 * Functions
 **************************************************************************/
void I2C_LCD_Init(void);
void I2C_LCD_Puts(char *szStr);
void I2C_LCD_Clear(void);
void I2C_LCD_NewLine(void);
void I2C_LCD_BackLight(uint8_t u8BackLight);

#endif	/* __LCD_I2C_H */