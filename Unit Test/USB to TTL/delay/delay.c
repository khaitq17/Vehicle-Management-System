#include "delay.h"

void TIM_Config()
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
	// Configure TIM2
	TIM_TimeBaseInitTypeDef TIM_InitStruct;
	
	TIM_InitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_InitStruct.TIM_Prescaler = 72 - 1;
	TIM_InitStruct.TIM_Period = 20000 - 1;
	TIM_InitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM2, &TIM_InitStruct);

	TIM_Cmd(TIM2, ENABLE);
}
	
/**************************************************************************
 * @brief   delay_ms
 * @details This function creates delay in milliseconds base on TIM2.
 * @param   milliseconds	Delay time in milliseconds
 * @return  void
 **************************************************************************/
void delay_ms(uint32_t milliseconds)
{
	while (milliseconds)
	{
		TIM_SetCounter(TIM2, 0);
		while(TIM_GetCounter(TIM2) < 1000);
		--milliseconds;
	}
}




