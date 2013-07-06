/*
test the rotary encoders
INT0 left A
INT1 left B

INT3 right A
INT4 right B

*/

#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>

#define BAUD 38400

#include <util/setbaud.h>

void port_init(void)
{
 DDRD = 0x00; 			//set PORTD (INT0 pin) direction as input
 PORTD = 0b11111111; 		//set PORTD pins floating
}


/*-------------------------------------------------------------------------
-----------------INITIALIZE THE UART--------------------------------------
--------------------------------------------------------------------------*/

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

/*-------------------------------------------------------------------------
-----------------INITIALIZE THE INTERRUPTS---------------------------------
--------------------------------------------------------------------------*/

void init_devices (void)
{
 cli(); 		 //Clears the global interrupts
 port_init();
 EICRA = 0b11111111;   //set INT0, INT1, INT2, INT3 as rising edge triggered
 //EICRB = 0b11111111;  //set INT4, INT5, INT6, INT7  as any change in level triggered
 EIMSK = 0b00001111;	 //INT0,INT1, INT2, INT3 external interrupts are enabled
 sei();			 //Enables the global interrupts
}

/*-------------------------------------------------------------------------
-----------------ISR CORRESPONDING TO LEFT MOTOR CHANNEL A-----------------
--------------------------------------------------------------------------*/
ISR(INT0_vect)                  //external interupt on INT7
{
 	serial_write_char('0');
 	//_delay_ms(500);                //Addition of delay is not recommended in ISR
                                //we have added for switch debouncing action 

// check the state of left channel B, if it is low, then increment left_count, else decrement left_count

}


/*-------------------------------------------------------------------------
-----------------ISR CORRESPONDING TO LEFT MOTOR CHANNEL B-----------------
--------------------------------------------------------------------------*/
ISR(INT1_vect)                  
{
 	serial_write_char('1');
 	//_delay_ms(500);                //Addition of delay is not recommended in ISR
                                //we have added for switch debouncing action 
// check the state of left channel A, if it is high, then increment left_count, else decrement left_count

}

/*-------------------------------------------------------------------------
-----------------ISR CORRESPONDING TO RIGHT MOTOR CHANNEL A-----------------
--------------------------------------------------------------------------*/

ISR(INT2_vect)                  
{
 	serial_write_char('2');
 	//_delay_ms(500);                //Addition of delay is not recommended in ISR
                                //we have added for switch debouncing action 
//check the state of right channel B, if it is low, then increment right_count, else decrement right_count
}

/*-------------------------------------------------------------------------
-----------------ISR CORRESPONDING TO RIGHT MOTOR CHANNEL B-----------------
--------------------------------------------------------------------------*/

ISR(INT3_vect)                  
{
 	serial_write_char('3');
 	//_delay_ms(500);                //Addition of delay is not recommended in ISR
                                //we have added for switch debouncing action 
// check the state of right channel A, if it is high, then increment right_count, else decrement right_count
}

int main(void)
{
uart0_init();
init_devices();
while(1);
}
