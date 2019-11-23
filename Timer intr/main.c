/*
 * Timer intr.c
 *
 * Created: 23/11/2019 13:35:52
 * Author : olive
 */ 

#include <avr/io.h>
#define  F_CPU 8000000UL
#include <avr/interrupt.h>
#include <avr/delay.h>

ISR(TIMER0_OVF_vect) 
{ 
	PORTC ^= (1<<PC0); /* Toggle PORTC PC0 */ 
	TCNT0 = 0xB2; /* At the end of each cycle: Reload start value to TCNT0 */
}

int main(void)
{
    DDRA = 0x07; // set pin A as output pins
	DDRC = 1<<PC0; // set pc0 as an output pin
	DDRD = 0; //set  port D as the output pin 
	PORTD = PORTD | 1<<PD2;   // Activate the pull-up resistor
	
	TIMSK = 1<<TOIE0;  // Enable the timer overflow interrupt
	
	
	TCNT0 = 0xA0;   // Loads the TCNT0, then counts for 10ms
	TCCR0 = 1<<CS00 | 1<<CS02;  // starts timer 0 with 1024 pre-scaler
	sei();    // enable the global interrupt
    while (1) 
    {
		PORTA = PORTA | 1<<PA0;
		_delay_ms(400);
		PORTA= PORTA & (~(1<<PA0));
		_delay_ms(400);
		PORTA  = PORTA  | 1<<PA1;
		_delay_ms(400);
		PORTA= PORTA & (~(1<<PA1));
		_delay_ms(400);
		PORTA = PORTA | 1<<PA2;
		_delay_ms(400);
		PORTA= PORTA & (~(1<<PA2));
		_delay_ms(400);
    }
}

