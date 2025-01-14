/***************************************************************************
 * @file    IT.c
 * @brief   Define functions related to interrupts
 * @details This file defines functions related to configure and handle 
 *					interrupts.
 * @version 1.0
 * @date    2024-10-22
 * @author  Tran Quang Khai
 ***************************************************************************/
#include "IT.h"

/**************************************************************************
 * Static variable that stores value to handle interrupts
 * This variable is only used within the scope of this source file (local scope)
 **************************************************************************/
static volatile uint16_t count = 0;

/**************************************************************************
 * @brief   NVIC_Config
 * @details This function configures the Nested Vectored Interrupt 
 *					Controller (NVIC), enables and sets priority for interrupts.
 * @param   none
 * @return  void
 **************************************************************************/
void NVIC_Config()
{
	NVIC_InitTypeDef NVIC_InitStruct;
	
	NVIC_InitStruct.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	
	NVIC_Init(&NVIC_InitStruct);
}

/**************************************************************************
 * @brief   TIM2_IRQHandler
 * @details This function is interrupt handler for TIM2, executes when 
 *					TIM2 generates an update interrupt.
 * @param   none
 * @return  void
 **************************************************************************/
void TIM2_IRQHandler()
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
	{
		count++;
		
		if (count >= 10) {
			count = 0;
			blinkLed();
		}
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	}
}