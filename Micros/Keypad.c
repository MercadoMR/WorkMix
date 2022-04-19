/*
 * Keypad.c
 *
 * Created: 16/01/2021 04:24:25 p. m.
 *  Author: MIMR
 */ 

#include <avr/io.h>
#include <avr/delay.h>
//#define F_CPU 1000000UL //1 MHz
#define F_CPU 16000000UL
#define BAUD 9600
#define BAUD_PRESCALER ( (F_CPU/(8UL * BAUD)) - 1)

void cfg_UART(unsigned int);
void UART_send(unsigned char);
unsigned char obtener_simbolo(unsigned char);
unsigned char numerico(unsigned char);
unsigned char alfabetico(unsigned char);
unsigned char extendido(unsigned char);


unsigned char modo = 0x01;
int
main(void)
{
	cfg_UART(BAUD_PRESCALER);
	volatile unsigned char leido;
    while (1)
    {
		PORTD &= 0x0F; // SALIDA PD7-PD4 (0000)
		PORTB = 0xFF; // SALIDA PB3-PB0 (1111) ????
		DDRB = 0x00; // MARCAR LECTURA PB3-PB0  resistencias pull-off(1111)
		DDRD |= 0xF0; // MARCAR ESCRITURA PD7-PD4 
		_delay_us(10);
    	leido = PINB & 0x0F; // LEER FILAS XXXX1011 (0f)
		
		PORTB = 0x00; // SALIDA PB3-PB0 (0000)
    	PORTD |= 0xF0; // SALIDA PD7-PD4 (1111) ????
		DDRD &= 0x0F; //  MARCAR LECTURA PD7-PD4  resistencias pull-off(1111)
    	DDRB = 0XFF; // MARCAR ESCRITURA PB3-PB0
    	_delay_us(10);
    	leido |= PIND & 0xF0; // LEER COLUMNAS 1101XXXX
		leido = obtener_simbolo(leido);
		if (leido != '-')
		{
				UART_send(leido);	
		}
		_delay_ms(800);
    }
}

void
cfg_UART(unsigned int baud_rate)
{

	/* Poner baud_rate */
	UBRR0H = (uint8_t)(baud_rate>>8);
	UBRR0L = (uint8_t)(baud_rate);
	/* Para el caso de 9600 a un 1 MHz se carga un doce en UBRR
	*/
	UCSR0A =  0x22;  //Double speed
	UCSR0B =  (1 << TXEN0); //UCSR0B = 0x18;
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); //UCSR0C = 0x06; Poner uno en las posiciones
}

void 
UART_send(unsigned char data){

	while(!(UCSR0A & (1<<UDRE0)));
	UDR0 = data;

}

unsigned char
obtener_simbolo(unsigned char leido)
{
	if (modo > 3) {
		modo = 1;
	}else if(leido == 0xEE) {
		modo += 1;
		return '#';
	}

	switch(modo)
	{
		case 1:
			return numerico (leido);
		break;
		case 2:
			return alfabetico (leido);
		break;
		case 3:
			return extendido (leido);
		break;
	}
	return '-'; // '0'
}

unsigned char
numerico(unsigned char leido)
{
	switch(leido)
	{
		/* Primera fila presionada */
		case 0x77:		return '0';		break;
		case 0xB7:		return '1';		break;
		case 0xD7:		return '2';		break;
		case 0xE7:		return '3';		break;
		/* Segunda fila presionada */
		case 0x7B:		return '4';		break;
		case 0xBB:		return '5';		break;
		case 0xDB:		return '6';		break;
		case 0xEB:		return '7';		break;
		/* Tercera fila presionada */
		case 0x7D:		return '8';		break;
		case 0xBD:		return '9';		break;
		case 0xDD:		return 'A';		break;
		case 0xED:		return 'B';		break;
		/* Cuarta fila presionada */
		case 0x7E:		return 'C';		break;
		case 0xBE:		return 'D';		break;
		case 0xDE:		return 'E';		break;
		case 0xEE:		return '#';		break;
	}
	return '-';
}

unsigned char
alfabetico(unsigned char leido)
{
	switch(leido)
	{
		/* Primera fila presionada */
		case 0x77:		return 'F';		break;
		case 0xB7:		return 'G';		break;
		case 0xD7:		return 'H';		break;
		case 0xE7:		return 'I';		break;
		/* Segunda fila presionada */
		case 0x7B:		return 'J';		break;
		case 0xBB:		return 'K';		break;
		case 0xDB:		return 'L';		break;
		case 0xEB:		return 'M';		break;
		/* Tercera fila presionada */
		case 0x7D:		return 'N';		break;
		case 0xBD:		return 0xD1; // Ñ
		case 0xDD:		return 'O';		break;
		case 0xED:		return 'P';		break;
		/* Cuarta fila presionada */
		case 0x7E:		return 'Q';		break;
		case 0xBE:		return 'R';		break;
		case 0xDE:		return 'S';		break;
		case 0xEE:		return '#';		break;
		default:	break;
	}
	return '-';
}

unsigned char
extendido(unsigned char leido)
{
	switch(leido)
	{
		/* Primera fila presionada */
		case 0x77:		return 'T';		break;
		case 0xB7:		return 'U';		break;
		case 0xD7:		return 'V';		break;
		case 0xE7:		return 'W';		break;
		/* Segunda fila presionada */
		case 0x7B:		return 'X';		break;
		case 0xBB:		return 'Y';		break;
		case 0xDB:		return 'Z';		break;
		case 0xEB:		return 'Á';		break;
		/* Tercera fila presionada */
		case 0x7D:		return 'É';		break;
		case 0xBD:		return 'Í';		break;	// Ñ 
		case 0xDD:		return 'Ó';		break;
		case 0xED:		return 'Ú';		break;
		/* Cuarta fila presionada */
		case 0x7E:		return '.';		break;
		case 0xBE:		return 0x20;	break; // Espacio en blanco
		case 0xDE:		return '\n';	break; // Salto de linea
		case 0xEE:		return '#';		break;
	}
	return '-';
}
