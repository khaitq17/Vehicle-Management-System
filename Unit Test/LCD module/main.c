#include "stm32f10x.h"      
#include "i2c_lcd.h"


int main(void)
{
	Delay_Init();
	I2C_LCD_Init();
	I2C_LCD_Clear();
	I2C_LCD_BackLight(1);
	
	Delay_Ms(3000);
	
	I2C_LCD_Puts("Test LCD module");
	Delay_Ms(2000);
	I2C_LCD_NewLine();
	I2C_LCD_Puts("Hello World!");
	
	while(1) 
	{
		
	}
}
		