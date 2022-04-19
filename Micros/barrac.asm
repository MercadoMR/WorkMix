#include <avr/io.h>
#include <util/delay.h>
#define F_CPU 1000000UL  /* Frecuencia con la que se trabaja 1MHz*/

int 
main(void)
{
	PORTC=0x03; /*Pull off habilitado*/
	DDRB=0xFF;  /*Marcar como salida*/
	while(1)
	{
		if( (PINC&0x01) == 0x00) /* Tambien con un solo =  ó !(PINC&0x01)*/
		{
			/*Prender bit por bit */
			PORTB=0x01;
			_delay_ms(125);
			PORTB=0x03;
			_delay_ms(125);
			PORTB=0x07;
			_delay_ms(125);
			PORTB=0x0F;
			_delay_ms(125);
			PORTB=0x1F;
			_delay_ms(125);
			PORTB=0x3F;
			_delay_ms(125);
			PORTB=0x7F;
			_delay_ms(125);
			PORTB=0xFF;
			_delay_ms(125);
			PORTB=0x00;
			_delay_ms(500); /*Dejar apagado medio segundo*/
		}else if(!(PINC&0x02))
		{
			PORTB=0x80;
			_delay_ms(125);
			PORTB=0xC0;
			_delay_ms(125);
			PORTB=0xE0;
			_delay_ms(125);
			PORTB=0xF0;
			_delay_ms(125);
			PORTB=0xF8;
			_delay_ms(125);
			PORTB=0xFC;
			_delay_ms(125);
			PORTB=0xFE; /*sIENTO QUE ESTE ESTÁ MAL XD */
			_delay_ms(125);
			PORTB=0xFF;
			_delay_ms(125);
			PORTB=0x00;
			_delay_ms(500); /*Dejar apagado medio segundo*/
		}

	}

}