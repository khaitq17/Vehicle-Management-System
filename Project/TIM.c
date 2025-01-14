/***************************************************************************
 * @file    TIM.c
 * @brief   Define functions related to Timer
 * @details This file defines functions for Timer, PWM.
 * @version 1.0
 * @date    2024-10-22
 * @author  Tran Quang Khai
 ***************************************************************************/
#include "TIM.h"

/**************************************************************************
 * @brief   TIM_Config
 * @details This function configures for Timer.
 * @param   none
 * @return  void
 **************************************************************************/
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
	
	// Configure Output Compare for TIM2
	TIM_OCInitTypeDef TIM_OCInitStruct;
	
	TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStruct.TIM_OutputState = ENABLE;
	TIM_OCInitStruct.TIM_Pulse = 500;
	TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;
	
	TIM_OC1Init(TIM2, &TIM_OCInitStruct);
	TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);
	
	// Enable TIM2 and interrupt for TIM2
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);	
	TIM_Cmd(TIM2, ENABLE);
	
	// Configure TIM3
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	
	TIM_InitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_InitStruct.TIM_Prescaler = 72 - 1;
	TIM_InitStruct.TIM_Period = 20000 - 1;
	TIM_InitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM3, &TIM_InitStruct);
	TIM_Cmd(TIM3, ENABLE);
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
		TIM_SetCounter(TIM3, 0);
		while(TIM_GetCounter(TIM3) < 1000);
		--milliseconds;
	}
}

/**************************************************************************
 * @brief   setPWM
 * @details This function sets pulse for channel 1 of TIM2.
 * @param   pulse		Compare value want to set for channel 1
 * @return  void
 **************************************************************************/
void setPWM(uint16_t pulse)
{
	TIM_SetCompare1(TIM2, pulse);
}