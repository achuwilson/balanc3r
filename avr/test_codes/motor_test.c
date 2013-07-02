#define F_CPU 16000000UL
#include<avr/io.h>
#include<util/delay.h>

#define _BV(bit) (1 << (bit))

void main (void)
{
//set all pins of PORTBto output
DDRB=0xff;
		//enable R motor
		PORTB|=_BV(PB6);
		//enable L motor
		PORTB|=_BV(PB5);
	while(1)
	{	
		
	
		//move R motor  bwd
		PORTB|=_BV(PB3);//|(0<<PB1);
		//PORTB&=!(1<<PB1);
		
		//2 sec delay
		_delay_ms(2000);
		
		//now stop
		PORTB&=~_BV(PB3);//|(1<<PB1);
		//PORTB&=!(1<<PB1);
	//PORTB=0x00;
		_delay_ms(4000);
	}
}
