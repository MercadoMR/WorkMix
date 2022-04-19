/*
 * Senial.c
 *
 * Created: 04/12/2020 05:22:26 p. m.
 * Author : MIMR
 * https://exploreembedded.com/wiki/AVR_External_Interrupts
 * https://www.csee.umbc.edu/~alnel1/cmpe311/discussions/AVR_Interrupts_in_C.pdf 
 * https://www.nongnu.org/avr-libc/user-manual/group__avr__interrupts.html
 * https://electronics.stackexchange.com/questions/5302/how-do-i-read-digital-input-on-atmega16
 * https://arduino.stackexchange.com/questions/56304/how-do-i-directly-access-a-memory-mapped-register-of-avr-with-c
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 1000000UL
#include <util/delay.h>

unsigned char temp;


ISR(INT0_vect)
{
	temp += 1;
	if (temp > 3)
	{
		temp = 0x00;
	}
}

int 
main(void)
{
	
    /* Replace with your application code */
	DDRB = 0x01;
	temp = 0x00;
	EICRA = 0x03;
	EIMSK = 0x01;
	sei();
    while (1) 
    {
		PORTB = 0x01;
		switch(temp)
		{
			case 1: //Senial de 100 Hz -> T = 0.010 s = 10ms. 5ms en alto y 5ms en bajo
			_delay_ms(5);
			PORTB = 0x00;
			_delay_ms(5);
			break;
			case 2: //Senial de 250 Hz -> T = 4 ms. 2ms en alto y 2ms en bajo
			_delay_ms(2);
			PORTB = 0x00;
			_delay_ms(2);
			break;
			case 3: //Senial de 990 Hz -> T = 1010 us. 505us en alto y 505us en bajo
			_delay_us(505);
			PORTB = 0x00;
			_delay_us(505);
			break;
			default: //Senial de 10 Hz -> T = 0.100 s = 100ms. 50ms en alto y 50ms en bajo
			_delay_ms(50);
			PORTB = 0x00;
			_delay_ms(50);			
			break;
		}
    }
	
}

