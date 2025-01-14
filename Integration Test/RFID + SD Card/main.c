#include "stm32f10x.h"         
#include "GPIO.h"
#include "delay.h"
#include "SPI.h"
#include "ff.h"
#include "fatfs.h"
#include "fatfs_sd.h"
#include <stdio.h>
#include <string.h>
#include "MFRC522.h"
#include <stdbool.h>

FATFS FatFs;  
FIL fil;    
UINT bw, br; 
FRESULT fr; 
TM_MFRC522_Status_t status;
uint8_t CardID[5];
uint8_t str[MFRC522_MAX_LEN];
char buffer[64];
uint8_t tempUID[5];
bool exists = false;

void addUIDToFile(const char* filename, uint8_t* uid);

int main(void)
{
	GPIO_Config();    
	SPI_Config();     
	TIMER_Config();   
	FATFS_Init();     
	TM_MFRC522_Init();
	
	fr = f_mount(&FatFs, "", 0);

	
	
	
	fr = f_open(&fil, "data.csv", FA_READ);
    if (fr == FR_OK) {
			f_read(&fil, buffer, sizeof(buffer) - 1, &br);
      buffer[br] = '\0';  
      f_close(&fil);
			LED_Blink(5);
    }
	
	/*
		
fr = f_open(&fil, "Hello.txt", FA_CREATE_ALWAYS | FA_WRITE);
  if (fr == FR_OK) {
		f_truncate(&fil);
		f_close(&fil);
		LED_Blink(3);
  }	
	*/
	
	/*
	while(1)
	{
		status = TM_MFRC522_Check(CardID);
		if (status == MI_OK) {
			fr = f_open(&fil, "data.csv", FA_READ);
    if (fr == FR_OK) {
        while (f_gets(buffer, sizeof(buffer), &fil)) {
            
			
            if (sscanf(buffer, "%2hhX,%2hhX,%2hhX,%2hhX,%2hhX", 
                       &tempUID[0], &tempUID[1], &tempUID[2], &tempUID[3], &tempUID[4]) == 5) {
                if (memcmp(tempUID, CardID, 5) == 0) {
                    exists = true; // UID dã t?n t?i
                    break;
                }
            }
        }
        f_close(&fil);
    }
	
    // 2. N?u UID chua t?n t?i, ghi vào file
    if (!exists) {
        fr = f_open(&fil, "data.csv", FA_WRITE | FA_OPEN_ALWAYS);
        if (fr == FR_OK) {
            // Di chuy?n con tr? d?n cu?i file
            f_lseek(&fil, f_size(&fil));
			
            char line[32];
            snprintf(line, sizeof(line), "%02X,%02X,%02X,%02X,%02X\n",
                     CardID[0], CardID[1], CardID[2], CardID[3], CardID[4]);
			
            f_write(&fil, line, strlen(line), &bw);
            f_close(&fil);
        }
    }
		}
		delay_ms(500);
	}
	*/
	
}

void addUIDToFile(const char* filename, uint8_t* uid)
{
    FIL file;
    FRESULT fr;
    char buffer[32];
    bool exists = false;

    // 1. Ki?m tra UID dã t?n t?i trong file chua
    fr = f_open(&file, filename, FA_READ);
    if (fr == FR_OK) {
        while (f_gets(buffer, sizeof(buffer), &file)) {
            uint8_t tempUID[5];
			
            if (sscanf(buffer, "%2hhX,%2hhX,%2hhX,%2hhX,%2hhX", 
                       &tempUID[0], &tempUID[1], &tempUID[2], &tempUID[3], &tempUID[4]) == 5) {
                if (memcmp(tempUID, uid, 5) == 0) {
                    exists = true; // UID dã t?n t?i
                    break;
                }
            }
        }
        f_close(&file);
    }
	
    // 2. N?u UID chua t?n t?i, ghi vào file
    if (!exists) {
        fr = f_open(&file, filename, FA_WRITE | FA_OPEN_ALWAYS);
        if (fr == FR_OK) {
            // Di chuy?n con tr? d?n cu?i file
            f_lseek(&file, f_size(&file));
			
            char line[32];
            snprintf(line, sizeof(line), "%02X,%02X,%02X,%02X,%02X\n",
                     uid[0], uid[1], uid[2], uid[3], uid[4]);
			
            UINT bw;
            f_write(&file, line, strlen(line), &bw);
            f_close(&file);
        }
    }
}