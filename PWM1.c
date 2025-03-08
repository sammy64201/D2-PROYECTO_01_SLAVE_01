/*
 * PWM1.c
 *
 * Created: 5/20/2024 9:16:55 PM
 *  Author: samue
 */ 
#include "PWM1.h"
void PWM_INIT(void)
{
	
	DDRB |= (1 << PB1) | (1 << PB2);					//OCIA y OCIB como salidas
	
	TCCR1A = (1 << COM1A1) | (1 << COM1B1) | (1 << WGM11);			//FAST PWM y preescaler de 8
	TCCR1B = (1 << WGM13) | (1 << WGM12) | (1 << CS11);
	ICR1 = 39999;
}

void Servo_Angle(uint8_t angle, uint8_t ServoNo)
{
	uint16_t pulse_width = 0;
	
	if (ServoNo == 1)
	{
		pulse_width = 1000 + ((uint32_t)angle * 4000) / 180;
		OCR1A = pulse_width;
	}
	if (ServoNo == 2)
	{
		pulse_width = 1000 + ((uint32_t)angle * 4000) / 180;
		OCR1B = pulse_width;
	}
	
}