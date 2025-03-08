/*
 * ADC.c
 *
 * Created: 2/2/2025 12:20:28 AM
 *  Author: samue
 */ 

#include "ADC.h"

volatile uint8_t pot1 = 0;
volatile uint8_t pot2 = 0;
volatile uint8_t canal_adc = 0;

void initADC(){
	ADMUX = 0;
	// REFERENCIA AVCC = 5V
	ADMUX |= (1 << REFS0);
	ADMUX &= ~(1 << REFS1);
	// JUSTIFICACION A LA IZQUIERDA
	ADMUX |= (1 << ADLAR);
	// PRESCALER 128
	ADCSRA = 0;
	ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
	// HABILITAR INTERRUPCI�N DE ADC
	ADCSRA |= (1 << ADIE);
	// HABILITAR ADC
	ADCSRA |= (1 << ADEN);
}

void iniciarADC(uint8_t canal){
	ADMUX = (ADMUX & 0xF8) | (canal & 0x07); // Seleccionar canal
	ADCSRA |= (1 << ADSC);  // Iniciar conversi�n
}


ISR(ADC_vect){
	if (canal_adc == 0){
		pot1 = ADCH;  // Guardar el valor de ADC0
		canal_adc = 0;
		//ADCSRA |= (1 << ADIF);
	}
	// 		} else {
	// 		pot2 = ADCH;  // Guardar el valor de ADC1
	// 		canal_adc = 0;

	iniciarADC(canal_adc); // Iniciar la siguiente conversi�n autom�ticamente
}


