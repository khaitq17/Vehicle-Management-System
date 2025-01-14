/***************************************************************************
 * @file    servo.h
 * @brief   Declare functions related to control Servo
 * @details This file includes functions to rotate Servo.
 * @version 1.0
 * @date    2024-10-22
 * @author  Tran Quang Khai
 ***************************************************************************/
#ifndef __SERVO_H
#define __SERVO_H

#include "TIM.h"          
           
/**************************************************************************
 * Macro defines constant for minimum and maximum pulse width of Servo
 * MIN_PULSE_WIDTH: Minimum pulse width (500)
 * MAX_PULSE_WIDTH: Maximum pulse width (2500)
 **************************************************************************/					 
#define MIN_PULSE_WIDTH	500			/* Minimum pulse width */
#define MAX_PULSE_WIDTH	2500		/* Maximum pulse width */

/**************************************************************************
 * @brief   getPulseByAngle
 * @param   angle			Angle that want Servo rotate to
 * @return  uint16_t	Return pulse width after calculate by angle
 **************************************************************************/
uint16_t getPulseByAngle(uint8_t angle);

/**************************************************************************
 * @brief   openBarrier
 * @param   none
 * @return  void
 **************************************************************************/
void openBarrier(void);

/**************************************************************************
 * @brief   closeBarrier
 * @param   none
 * @return  void
 **************************************************************************/
void closeBarrier(void);

#endif /* __SERVO_H */