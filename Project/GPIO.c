/***************************************************************************
 * @file    GPIO.c
 * @brief   Define functions related to GPIO
 * @details This file defines functions for GPIO of RFID module, 
 *					SD card module, Servo, LED, a module use UART to debug.
 * @version 1.0
 * @date    2024-10-22
 * @author  Tran Quang Khai
 ***************************************************************************/
#include "GPIO.h"

/**************************************************************************
 * @brief   GPIO_Config
 * @details This function configures GPIO for RFID module, SD card module, 
 *					Servo, LED, UART.
 * @param   none
 * @return  void
 **************************************************************************/
void GPIO_Config()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	GPIO_InitTypeDef GPIO_InitStruct;
	
	// GPIO configure for MFRC522
	RCC_APB2PeriphClockCmd(MFRC522_GPIO_RCC, ENABLE);
	
	GPIO_InitStruct.GPIO_Pin = MFRC522_SCK_PIN | MFRC522_MOSI_PIN;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(MFRC522_GPIO, &GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Pin = MFRC522_MISO_PIN;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(MFRC522_GPIO, &GPIO_InitStruct);
	
	// GPIO configure for SD Card
	RCC_APB2PeriphClockCmd(SDCARD_GPIO_RCC, ENABLE);
	
	GPIO_InitStruct.GPIO_Pin = SDCARD_SCK_PIN | SDCARD_MOSI_PIN;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(SDCARD_GPIO, &GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Pin = SDCARD_MISO_PIN;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(SDCARD_GPIO, &GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Pin = SDCARD_CS_PIN;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(SDCARD_GPIO, &GPIO_InitStruct);
	GPIO_SetBits(SDCARD_GPIO, SDCARD_CS_PIN);
	
	// GPIO configure for Servo
	RCC_APB2PeriphClockCmd(SERVO_GPIO_RCC, ENABLE);
	
	GPIO_InitStruct.GPIO_Pin = SERVO_PIN;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(SERVO_GPIO, &GPIO_InitStruct);
	
	// GPIO configure for LED
	RCC_APB2PeriphClockCmd(LED_GPIO_RCC, ENABLE);
	
	GPIO_InitStruct.GPIO_Pin = LED_PIN;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(LED_GPIO, &GPIO_InitStruct);
	GPIO_SetBits(LED_GPIO, LED_PIN);
	
	// GPIO configure for UART
	RCC_APB2PeriphClockCmd(UART_GPIO_RCC, ENABLE);
	
	GPIO_InitStruct.GPIO_Pin = UART_RX_PIN;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(UART_GPIO, &GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Pin = UART_TX_PIN;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(UART_GPIO, &GPIO_InitStruct);
}

/**************************************************************************
 * @brief   MFRC522_InitPins
 * @details This function initializes GPIO pin for RFID module.
 * @param   none
 * @return  void
 **************************************************************************/
void MFRC522_InitPins()
{
	RCC_APB2PeriphClockCmd(MFRC522_GPIO_RCC, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStruct;
	
	GPIO_InitStruct.GPIO_Pin = MFRC522_CS_PIN;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(MFRC522_GPIO, &GPIO_InitStruct);
	
	GPIO_SetBits(MFRC522_GPIO, MFRC522_CS_PIN);
}

/**************************************************************************
 * @brief   blinkLed
 * @details This function sets/resets bit to blink LED.
 * @param   none
 * @return  void
 **************************************************************************/
void blinkLed()
{
	GPIO_ResetBits(LED_GPIO, LED_PIN);
	delay_ms(1000);
	GPIO_SetBits(LED_GPIO, LED_PIN);
	delay_ms(1000);
}