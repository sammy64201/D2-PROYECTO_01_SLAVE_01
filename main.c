/*
 * D2-PROYECTO_01-SLAVE1_01.c
 *
 * Created: 3/2/2025 2:48:52 AM
 * Author : samue
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>


#include "ADC/ADC.h"
#include "I2C/I2C.h"
#include "PWM1/PWM1.h"
#include "UART/UART.h"
#include "PWM0/PWM0.h"



#define SLAVE_ADDRESS 0x30  // Direccio?n I2C del esclavo

uint8_t buffer = 0;
volatile uint8_t valorADC = 0;
volatile uint8_t valor_luz = 0;
uint16_t angulo_servo;
char buffer_UART [6];
uint8_t recibido_i2c = 0;
uint8_t bandera;
volatile char banderita[8];

void setup(){
	cli();  // Deshabilitar interrupciones

	initADC();
	iniciarADC(0);
	I2C_Slave_Init(SLAVE_ADDRESS);
	//init_PWM1();
	PWM_INIT();
	initUART9600();
	
	sei();
}





int main(void)
{
	
	setup();

	
	
	
	while (1)
	{
		valor_luz = pot1;
		if (buffer == 1){
			bandera = 1;
		}else if (buffer == 0){
			bandera = 0;
		}
		
		if (bandera == 1){
			Servo_Angle(90, 1);
		}else if (bandera == 0){
			if (valor_luz < 30){
				Servo_Angle(90, 1);
				} else {
				Servo_Angle(0,1);
				}
		
		}

		sprintf(banderita, "BANDERITA: %d\r\n", bandera);
		WriteTextUART(banderita);	

	}
	

}


ISR(TWI_vect){
	uint8_t estado;
	estado = TWSR & 0xFC;
	switch(estado){
		case 0x60:
		case 0x70:
			TWCR |= (1<< TWINT);
		break;
		
		case 0x80:
		case 0x90:
			buffer = TWDR;
			TWCR |= (1<< TWINT);
			
		break;
		
		case 0xA8:
		case 0xB8:
			TWDR = valor_luz;
			TWCR = (1 << TWEN)|(1<<TWIE)|(1<<TWINT)|(1<<TWEA);
		break;
		
		default:
			TWCR |= (1<<TWINT)|(1<<TWSTO);
		break;
	}
}