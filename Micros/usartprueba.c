/*
 * USARTPrueba.c
 *
 * Created: 11/12/2020 10:02:46 p. m.
 * Author : MIMR
 https://hekilledmywire.wordpress.com/2011/01/05/using-the-usartserial-tutorial-part-2/
 http://maxembedded.com/2013/09/the-usart-of-the-avr/
 */ 
//Pagina 195 
#include <avr/io.h>
#define F_CPU 1000000UL //1 MHz
#define BAUD 9600
#define BAUD_PRESCALER ( (F_CPU/(8UL * BAUD)) - 1)   
/* Preescalador de baudios para configurar 
   el registro (UBRR) Baud Rate Register  
   A 1M conviene poner velocidad al doble 
   para un error de 0.2 
*/

void cfg_UART(unsigned int);
unsigned char UART_receive(void);
void UART_send( unsigned char data);
//void UART_putstring(char* StringPtr);

int 
main(void)
{
	cfg_UART(BAUD_PRESCALER);
	DDRB = 0x00;
    /* Replace with your application code */
	unsigned char dato = 'a';
    while (1) 
    {
		//dato = UART_receive();
		//dato++;
		UART_send(dato); 
    }
}

/* Start and setup of the UART */
void
cfg_UART(unsigned int baud_rate)
{
	
	/* Poner baud_rate */
	UBRR0H = (uint8_t)(baud_rate>>8);
	UBRR0L = (uint8_t)(baud_rate);
	/* Para el caso de 9600 a un 1 MHz se carga un doce en UBRR
	*/
	UCSR0A =  0x22;  //Double speed	
	UCSR0B =  (1 << RXEN0) | (1 << TXEN0); //UCSR0B = 0x18;
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); //UCSR0C = 0x06; Poner uno en las posiciones
	
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);

}

unsigned char UART_receive(void){
	
	while(!(UCSR0A & (1<<RXC0)));
	return UDR0;
	
}

void UART_send( unsigned char data){
	
	while(!(UCSR0A & (1<<UDRE0)));
	UDR0 = data;
	
}

/*
void UART_putstring(char* StringPtr){
	
	while(*StringPtr != 0x00){
		USART_send(*StringPtr);
	StringPtr++;}
	
}
*/