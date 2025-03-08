/*
 * ADC.h
 *
 * Created: 2/2/2025 12:20:13 AM
 *  Author: samue
 */ 


#ifndef ADC_H_
#define ADC_H_

#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>

extern volatile uint8_t canal_adc;
extern volatile uint8_t pot1, pot2;

void initADC(void);
void iniciarADC(uint8_t canal);


#endif /* ADC_H_ */