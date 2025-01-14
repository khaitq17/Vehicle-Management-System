/***************************************************************************
 * @file    GPIO.h
 * @brief   Declare functions related to GPIO
 * @details This file includes macros and functions for GPIO of RFID module, 
 *					SD card module, Servo, LED, a module use UART to debug.
 * @version 1.0
 * @date    2024-10-22
 * @author  Tran Quang Khai
 ***************************************************************************/
#ifndef __GPIO_H
#define __GPIO_H

#include "stm32f10x_gpio.h"                         
#include "TIM.h"

/**************************************************************************
 * Define GPIO pin, port, RCC for SPI to use RFID module 
 **************************************************************************/
#define MFRC522_CS_PIN		GPIO_Pin_12						/* RFID CS Pin */
#define MFRC522_SCK_PIN		GPIO_Pin_13						/* RFID SCK Pin */
#define MFRC522_MISO_PIN	GPIO_Pin_14						/* RFID MISO Pin */
#define MFRC522_MOSI_PIN	GPIO_Pin_15						/* RFID MOSI Pin */
#define MFRC522_GPIO			GPIOB									/* RFID GPIO */
#define MFRC522_GPIO_RCC	RCC_APB2Periph_GPIOB	/* GPIO RCC for RFID */

/**************************************************************************
 * Macros set/reset logical state of RFID CS Pin
 * MFRC522_CS_LOW: Reset CS Pin
 * MFRC522_CS_HIGH: Set CS Pin
 **************************************************************************/
#define MFRC522_CS_LOW		GPIO_ResetBits(MFRC522_GPIO, MFRC522_CS_PIN)
#define MFRC522_CS_HIGH		GPIO_SetBits(MFRC522_GPIO, MFRC522_CS_PIN)

/**************************************************************************
 * Define GPIO pin, port, RCC for SPI to use SD card module 
 **************************************************************************/
#define SDCARD_CS_PIN			GPIO_Pin_4						/* SD Card CS Pin */
#define SDCARD_SCK_PIN		GPIO_Pin_5						/* SD Card SCK Pin */
#define SDCARD_MISO_PIN		GPIO_Pin_6						/* SD Card MISO Pin */
#define SDCARD_MOSI_PIN		GPIO_Pin_7						/* SD Card MOSI Pin */
#define SDCARD_GPIO				GPIOA									/* SD Card GPIO */
#define SDCARD_GPIO_RCC		RCC_APB2Periph_GPIOA	/* GPIO RCC for SD Card */

/**************************************************************************
 * Define GPIO pin, port, RCC for Servo
 **************************************************************************/
#define SERVO_PIN					GPIO_Pin_0						/* Servo Pin */
#define SERVO_GPIO				GPIOA									/* Servo GPIO */
#define SERVO_GPIO_RCC		RCC_APB2Periph_GPIOA	/* GPIO RCC for Servo */

/**************************************************************************
 * Define GPIO pin, port, RCC for LED
 **************************************************************************/
#define LED_PIN						GPIO_Pin_13						/* LED Pin */
#define LED_GPIO					GPIOC									/* LED GPIO */
#define LED_GPIO_RCC			RCC_APB2Periph_GPIOC	/* GPIO RCC for LED */

/**************************************************************************
 * Define GPIO pin, port, RCC for a module use UART to debug
 **************************************************************************/
#define UART_TX_PIN				GPIO_Pin_9						/* UART TX Pin */
#define UART_RX_PIN				GPIO_Pin_10						/* UART RX Pin */
#define UART_GPIO					GPIOA									/* UART GPIO */
#define UART_GPIO_RCC			RCC_APB2Periph_GPIOA	/* GPIO RCC for UART */

/**************************************************************************
 * Define GPIO pin, port, RCC for I2C to use LCD module
 **************************************************************************/
#define I2C_SCL_PIN				GPIO_Pin_6						/* I2C SCL Pin */
#define I2C_SDA_PIN				GPIO_Pin_7						/* I2C SDA Pin */
#define I2C_GPIO					GPIOB									/* I2C GPIO */
#define I2C_GPIO_RCC			RCC_APB2Periph_GPIOB	/* GPIO RCC for I2C */

/**************************************************************************
 * @brief   GPIO_Config
 * @param   none
 * @return  void
 **************************************************************************/
void GPIO_Config(void);

/**************************************************************************
 * @brief   MFRC522_InitPins
 * @param   none
 * @return  void
 **************************************************************************/
void MFRC522_InitPins(void);

/**************************************************************************
 * @brief   blinkLed
 * @param   none
 * @return  void
 **************************************************************************/
void blinkLed(void);

#endif /* __GPIO_H */