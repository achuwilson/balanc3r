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
#include <stdlib.h>

#define BAUD 38400

#include <util/setbaud.h>

int64_t count;
char str[20];

void port_init(void)
{
 DDRD = 0x00; 			//set PORTD (INT0 pin) direction as input
// PORTD = 0b00000000; 		//set PORTD pins floating
PORTD = 0xff;
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

void serial_write_string(char* StringPtr){

while(*StringPtr != 0x00){    //Here we check if there is still more chars to send, this is done checking the actual char and see if it is different from the null char
 serial_write_char(*StringPtr);    //Using the simple send function we send one char at a time
 StringPtr++;}        //We increment the pointer so we can read the next char
}


/*-------------------------------------------------------------------------
-----------------INITIALIZE THE INTERRUPTS---------------------------------
--------------------------------------------------------------------------*/

void init_devices (void)
{
 cli(); 		 //Clears the global interrupts
 port_init();
 EICRA = 0b01010101;   //set INT0, INT1, INT2, INT3 as rising edge triggered
 EICRB = 0b00000000;  //set INT4, INT5, INT6, INT7  as any change in level triggered
 EIMSK = 0b00001111;	 //INT0,INT1, INT2, INT3 external interrupts are enabled
 sei();			 //Enables the global interrupts
}

/*-------------------------------------------------------------------------
-----------------ISR CORRESPONDING TO LEFT MOTOR CHANNEL A-----------------
--------------------------------------------------------------------------*/
int Position=0;
ISR(INT0_vect)                  //external interupt on INT7
{/* Static variables for position calculation */
//static unsigned char state = 0xFF;
//unsigned char new_state;
//new_state = (PIND & (_BV(PD0) | _BV(PD1))); /* Read encoder state */
/* Update position value */
/*	if (state!=new_state) {
		switch (state) {
			case 0x00:
				if (new_state==0x01)
					Position++;
				else
					Position--;
				break;
			case 0x01:
				if (new_state==0x03)
					Position++;
				else
					Position--;
				break;
			case 0x03:
				if (new_state==0x02)
					Position++;
				else
					Position--;
				break;
			case 0x02:
				if (new_state==0x00)
					Position++;
				else
					Position--;
				break;
				}
		state = new_state;
			}

serial_write_char(Position);
*///count++;
// 	serial_write_char('0');
 	//_delay_ms(500);                //Addition of delay is not recommended in ISR
                                //we have added for switch debouncing action 

// check the state of left channel B, if it is low, then increment left_count, else decrement left_count

	/*if(PIND&0b00000010==0b00000010)
		{
//		count--;
		serial_write_char('f');
		}
	else if(PIND&0b00000010==0b00000000)
		{serial_write_char('r');
		}
		
	else
		{
		serial_write_char('U');
		}
	*/	//serial_write_char(PIND&0b00000011);
		serial_write_char('0');

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
/*	if(PIND&0b00000001==1)
		{
		count++;
		}
	else
		count--;
*/
}


ISR(INT2_vect)
{
//count++;
serial_write_char('2');
}

/*-------------------------------------------------------------------------
-----------------ISR CORRESPONDING TO RIGHT MOTOR CHANNEL A-----------------
--------------------------------------------------------------------------*/
ISR(INT3_vect)                  
{
 	serial_write_char('3');
 	//_delay_ms(500);                //Addition of delay is not recommended in ISR
                                //we have added for switch debouncing action 
// check the state of right channel A, if it is high, then increment right_count, else decrement right_count
}


ISR(INT4_vect)                  
{
 	serial_write_char('4');
	
 	//_delay_ms(500);                //Addition of delay is not recommended in ISR
                                //we have added for switch debouncing action 
//check the state of right channel B, if it is low, then increment right_count, else decrement right_count
}

/*-------------------------------------------------------------------------
-----------------ISR CORRESPONDING TO RIGHT MOTOR CHANNEL B-----------------
--------------------------------------------------------------------------*/


ISR(INT5_vect)                  
{
 	serial_write_char('5');
	
 	//_delay_ms(500);                //Addition of delay is not recommended in ISR
                                //we have added for switch debouncing action 
//check the state of right channel B, if it is low, then increment right_count, else decrement right_count
}
ISR(INT7_vect)
{
serial_write_char('7');

/*if(PIND&0b01000000==PIND&0b10000000)
	{		
	count++;
	}
else 
	{
	count--;
	}

serial_write_char(count);
*/
}

ISR(INT6_vect)
{
//count++;
serial_write_char('6');
}

int main(void)
{

uart0_init();
	//DDRD &= ~(1 << PIN7);
	//PORTD |= (1 << PIN7);
	//EICRB = (1 << ISC70);
	//EIMSK |= (1 << INT7);
	//sei();
//DDRD=0b00000001;
//PORTD=0xff;
init_devices();
//serial_write_char('s');
while(1) ; 
	/*{
	if(PIND&0b00000010==0b00000010)
	{
	PORTD|=0xff;
	_delay_ms(550);
	PORTD&=0x00;
	_delay_ms(550);
	}

	else
		PORTD&=!(1<<PD0);

//	itoa(count, str, 16);
//	serial_write_string(str);
//	serial_write_char(count);
//	serial_write_char('p');
//	serial_write_char('\n');
	}*/
}
