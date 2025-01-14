/***************************************************************************
 * @file    servo.c
 * @brief   Define functions related to control Servo
 * @details This file defines functions to rotate Servo.
 * @version 1.0
 * @date    2024-10-22
 * @author  Tran Quang Khai
 ***************************************************************************/
#include "servo.h"

/**************************************************************************
 * @brief   getPulseByAngle
 * @details This function calculates pulse width by angle when use Servo
 *					180 degrees.
 * @param   angle			Angle that want Servo rotate to
 * @return  uint16_t	Return pulse width after calculate by angle
 **************************************************************************/
uint16_t getPulseByAngle(uint8_t angle)
{
	return (uint16_t) (((MAX_PULSE_WIDTH) - (MIN_PULSE_WIDTH)) * angle / 180) + (MIN_PULSE_WIDTH);
}

/**************************************************************************
 * @brief   openBarrier
 * @details This function rotates Servo to open the barrier. When scan 
 *					a valid card, Servo will rotate from 0 to 90 degrees in 500 ms.
 * @param   none
 * @return  void
 **************************************************************************/
void openBarrier()
{
	uint16_t initialPulse = getPulseByAngle(0);
	uint16_t finalPulse = getPulseByAngle(90);
	uint16_t stepPulse = (finalPulse - initialPulse) / 25;
	
	for (uint16_t pulse = initialPulse; pulse <= finalPulse; pulse += stepPulse) {
		setPWM(pulse);
		delay_ms(20);
	}
}

/**************************************************************************
 * @brief   closeBarrier
 * @details This function rotates Servo to close the barrier. After open  
 *					the barrier in a specific time, Servo will rotate from 90 to 0 
 *					degrees in 500 ms.
 * @param   none
 * @return  void
 **************************************************************************/
void closeBarrier()
{
	uint16_t initialPulse = getPulseByAngle(90);
	uint16_t finalPulse = getPulseByAngle(0);
	uint16_t stepPulse = (initialPulse - finalPulse) / 25;
	
	for (uint16_t pulse = initialPulse; pulse >= finalPulse; pulse -= stepPulse) {
		setPWM(pulse);
		delay_ms(20);
	}
}