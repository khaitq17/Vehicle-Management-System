/***************************************************************************
 * @file    TIM.h
 * @brief   Declare functions related to Timer
 * @details This file includes functions for Timer, PWM.
 * @version 1.0
 * @date    2024-10-22
 * @author  Tran Quang Khai
 ***************************************************************************/
#ifndef __TIM_H
#define __TIM_H

#include "stm32f10x_tim.h" 

// Use TIM2 to configure Timer and PWM

/**************************************************************************
 * @brief   TIM_Config
 * @param   none
 * @return  void
 **************************************************************************/
void TIM_Config(void);

/**************************************************************************
 * @brief   delay_ms
 * @param   milliseconds	Delay time in milliseconds
 * @return  void
 **************************************************************************/
void delay_ms(uint32_t milliseconds);

/**************************************************************************
 * @brief   setPWM
 * @param   pulse		Compare value want to set for channel 1
 * @return  void
 **************************************************************************/
void setPWM(uint16_t pulse);

#endif	/* __TIM_H */