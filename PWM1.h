/*
 * PWM1.h
 *
 * Created: 5/20/2024 9:16:31 PM
 *  Author: samue
 */ 


#ifndef PWM1_H_
#define PWM1_H_

#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/delay.h>
void PWM_INIT(void);

void Servo_Angle(uint8_t angle, uint8_t ServoNo);




#endif /* PWM1_H_ */