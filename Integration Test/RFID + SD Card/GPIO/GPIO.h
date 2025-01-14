#ifndef __GPIO_H
#define	__GPIO_H

#include "stm32f10x.h"       

/**************************************************************************
 * Define GPIO pin, port, RCC for SPI to use RFID module 
 **************************************************************************/
#define MFRC522_CS_PIN		GPIO_Pin_12						/* RFID CS Pin */
#define MFRC522_SCK_PIN		GPIO_Pin_13						/* RFID SCK Pin */
#define MFRC522_MISO_PIN	GPIO_Pin_14						/* RFID MISO Pin */
#define MFRC522_MOSI_PIN	GPIO_Pin_15						/* RFID MOSI Pin */
#define MFRC522_GPIO			GPIOB									/* RFID GPIO */
#define MFRC522_GPIO_RCC	RCC_APB2Periph_GPIOB	/* RFID RCC for GPIO */

/**************************************************************************
 * Macros set/reset logical state of RFID CS Pin
 * MFRC522_CS_LOW: Reset CS Pin
 * MFRC522_CS_HIGH: Set CS Pin
 **************************************************************************/
#define MFRC522_CS_LOW		GPIO_ResetBits(MFRC522_GPIO, MFRC522_CS_PIN)
#define MFRC522_CS_HIGH		GPIO_SetBits(MFRC522_GPIO, MFRC522_CS_PIN)

#define SDCARD_CS_PIN		GPIO_Pin_4
#define SDCARD_SCK_PIN	GPIO_Pin_5
#define SDCARD_MISO_PIN	GPIO_Pin_6
#define SDCARD_MOSI_PIN	GPIO_Pin_7
#define SDCARD_GPIO			GPIOA
#define SDCARD_GPIO_RCC	RCC_APB2Periph_GPIOA

void GPIO_Config(void);
void LED_Blink(uint8_t time);
void MFRC522_InitPins(void);
#endif
