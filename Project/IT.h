/***************************************************************************
 * @file    IT.h
 * @brief   Declare functions related to interrupts
 * @details This file includes functions related to configure and handle 
 *					interrupts.
 * @version 1.0
 * @date    2024-10-22
 * @author  Tran Quang Khai
 ***************************************************************************/
#ifndef __IT_H
#define __IT_H

#include "stm32f10x.h"           
#include "TIM.h"
#include "GPIO.h"

/**************************************************************************
 * @brief   NVIC_Config
 * @param   none
 * @return  void
 **************************************************************************/
void NVIC_Config(void);

/**************************************************************************
 * @brief   TIM2_IRQHandler
 * @param   none
 * @return  void
 **************************************************************************/
void TIM2_IRQHandler(void);

#endif /* __IT_H */