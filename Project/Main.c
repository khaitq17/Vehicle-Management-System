/***************************************************************************
 * @file    Main.c
 * @brief   Main program
 * @details This file is the main program for vehicle management system.
 * @version 1.0
 * @date    2024-10-22
 * @author  Tran Quang Khai
 ***************************************************************************/
#include "Main.h"

/**************************************************************************
 * Global variables 
 **************************************************************************/
FATFS fs;											/* Store file system information of the SD card */
FIL file;											/* Store information about open files in the file system */
FRESULT fr;										/* Store the result of file operations */
char line[128];								/* Store a line of text when reading/writing from a file */
TM_MFRC522_Status_t status;		/* Store the status of the RFID module MFRC522 */
uint8_t cardID[5];						/* Store the UID of the RFID tag (5 bytes) */
Node* uidList = NULL;					/* Store a linked list of RFID tag UIDs */
uint8_t uids[MAX_UIDS][5]; 		/* Store UIDs of the system */
int uidCount = 0;							/* Store number of UIDs of the system */

/**************************************************************************
 * @brief   Main function
 * @details This function is the main program to manage system, includes
 *					configure necessary peripherals and modules, load file to RAM
 *					and add UIDs to linked list, scan RFID card and check if UID 
 *					already exists in linked list to control servo.
 **************************************************************************/
int main(void)
{
	/* System initialization */
	GPIO_Config();
	SPI_Config();
	UART_Config();
	TIM_Config();
	TM_MFRC522_Init();
	FATFS_Init();
	
	printf("Welcome to the vehicle management system\n");
	
	/* Mount SD Card */
	fr = f_mount(&fs, "", 0);
	if (fr == FR_OK) {
		printf("SD Card mounted successfully.\n");
	}
	
	/* Load list from CSV file */
	fr = f_open(&file, "data.csv", FA_READ);
  if (fr == FR_OK) {
		while (f_gets(line, sizeof(line), &file)) {
			if (sscanf(line, "%2hhX,%2hhX,%2hhX,%2hhX,%2hhX",
                   &cardID[0], &cardID[1], &cardID[2], &cardID[3], &cardID[4]) == 5) {
				addNode(&uidList, cardID);
			}
		}
		blinkLed();
  }
	
	f_close(&file);
	
	/* Convert linked list to array and sort array to use binary search */
	uidCount = convertListToArray(uidList, uids, MAX_UIDS);
	
	sortUIDs(uids, uidCount);
	
	/* Scan RFID card and check */
	printf("Place your card on the RFID reader\n");
	
	while(1)
	{
		status = TM_MFRC522_Check(cardID);
		if (status == MI_OK) {
			printf("Card detected! UID: %02X,%02X,%02X,%02X,%02X\n", 
						cardID[0], cardID[1], cardID[2], cardID[3], cardID[4]);
			
			if (binarySearchUID(uids, uidCount, cardID)) {
				printf("Valid card! Opening barrier...\n");
				openBarrier();
				delay_ms(3000);
				closeBarrier();
			} else {
				printf("Invalid card!\n");
			}			
		}
	}
	
	return 0;
}

/**************************************************************************
 * Define printf to use UART
 **************************************************************************/
int fputc(int ch, FILE *f)
{
	while (!USART_GetFlagStatus(USART1, USART_FLAG_TXE));
	USART_SendData(USART1, (uint8_t)ch);
	while (!USART_GetFlagStatus(USART1, USART_FLAG_TC)){}
    
  return ch;
}