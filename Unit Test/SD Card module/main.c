#include "stm32f10x.h"         
#include "GPIO.h"
#include "delay.h"
#include "SPI.h"
#include "ff.h"
#include "fatfs.h"
#include "fatfs_sd.h"
#include <stdio.h>
#include <string.h>

void clearFile(const char* filename);

FATFS FatFs;  
FIL fil;    
UINT bw, br; 
FRESULT fr; 
char buffer[50];

int main(void)
{
	GPIO_Config();    
	SPI_Config();     
	TIMER_Config();   
	FATFS_Init();     
	
	
	fr = f_mount(&FatFs, "", 0); 
	/*
	if (fr == FR_OK) {
		fr = f_open(&fil, "Hello.txt", FA_WRITE | FA_CREATE_ALWAYS);	 
		if (fr == FR_OK) {
			f_write(&fil, "Tran Quang Khai", 15, &bw);	
			fr = f_close(&fil);							
			if (fr == FR_OK && bw == 15) {		 
				while (1) {
					LED_Blink(1);
				}
			}
		}
	}
	*/
	
	fr = f_open(&fil, "data.csv", FA_READ);
    if (fr == FR_OK) {
			f_read(&fil, buffer, sizeof(buffer) - 1, &br);
      buffer[br] = '\0';  
      f_close(&fil);
    }
	
	/*```	
fr = f_open(&fil, "Hello.txt", FA_CREATE_ALWAYS | FA_WRITE);
  if (fr == FR_OK) {
		f_truncate(&fil);
		f_close(&fil);
		LED_Blink(3);
  }	
	
		fr = f_open(&fil, "Hello.txt", FA_READ);
    if (fr == FR_OK) {
			f_read(&fil, buffer, sizeof(buffer) - 1, &br);
      buffer[br] = '\0';  
      f_close(&fil);
      if (br > 0) {
				while (1) {
					LED_Blink(1);
        }
      }
    }
	*/
  
	
	

	while(1) 
	{
		
	}
}

void clearFile(const char* filename)
{
	FIL file;
  FRESULT fr;
	
	fr = f_open(&file, filename, FA_CREATE_ALWAYS | FA_WRITE);
  if (fr == FR_OK) {
		f_truncate(&file);
		f_close(&file);
  }
}
