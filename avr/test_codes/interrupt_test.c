#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>

#define BAUD 38400

#include <util/setbaud.h>

void port_init(void)
{
 DDRD |= 0xFE; 			//set PORTD (INT0 pin) direction as input
 PORTD |= 0x01; 		//set PORTD pins floating
}

void uart0_init(void)
{
UCSR0B = 0x00; //disable while setting baud rate
UBRR0H = UBRRH_VALUE;
UBRR0L = UBRRL_VALUE;
UCSR0C = _BV(UCSZ01) | _BV(UCSZ00);
UCSR0B = _BV(RXEN0) | _BV(TXEN0);
}

void serial_write_char(unsigned char c)
{
	while ( !(UCSR0A & (1 << UDRE0)) )
		;
	UDR0 = c;
}

void init_devices (void)
{
 cli(); 		 //Clears the global interrupts
 port_init();
 EICRA |= 0x00;  //Low level on INT0 pin selection for interrupt request
 EIMSK |= 0x01;	 //INT0 external interrupt is enabled
 sei();			 //Enables the global interrupts
}

ISR(INT0_vect)                  //external interupt on INT0
{
 serial_write_char('i');
 _delay_ms(500);                //Addition of delay is not recommended in ISR
                                //we have added for switch debouncing action 
}


int main(void)
{
uart0_init();
init_devices();
while(1);
}
