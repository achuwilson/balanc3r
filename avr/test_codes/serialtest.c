// now reads data from serial port and control the motor speed
#define F_CPU 16000000UL
#include <avr/io.h>

#include <util/delay.h>
#include <stdio.h>

#define BAUD 38400

#include <util/setbaud.h>
#include "motor_pwm.c"

void uart0_init(void)
{
UCSR0B = 0x00; //disable while setting baud rate
UBRR0H = UBRRH_VALUE;
UBRR0L = UBRRL_VALUE;
UCSR0C = _BV(UCSZ01) | _BV(UCSZ00);
UCSR0B = _BV(RXEN0) | _BV(TXEN0);
}

int serial_read_char()
{
 while(!(UCSR0A & (1<<RXC0)))
   {
      //Do nothing
   }

   //Now USART has got data from host
   //and is available is buffer

   return UDR0;
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


int main(void)
{
	char i = 0;
	char *str = "the quick brown fox jumps over the lazy dog. 1234567890\r\n";
	char *str2 = "got s\r\n";
	int l_speed,r_speed;
	uart0_init();
	MOTOR_Init_Ports();
	MOTOR_Init_Timer1_PWM();
	MOTOR_Motor2_Set_PWMduty(40);
	MOTOR_PWM_Motor2_Forward();
 	serial_write_string("init over");

 	while(1)
		{
		i=serial_read_char();
		serial_write_char(i);
		if(i=='s')
			{serial_write_char('g');
			
	
			r_speed=serial_read_char();
			MOTOR_Motor2_Set_PWMduty(r_speed);


			}
		//serial_write_string(str); 
		//_delay_ms(500);	
		//if (serial_read_char=='s')

		//{serial_write_string(str2); 
		//_delay_ms(500);	
		//}
		//else
		//{serial_write_string(str); 
		//_delay_ms(500);	
		//}
		
/* This method also works ;)
			serial_write_char(str[i++]);
			if (str[i] == '\0') {
				i = 0;
				_delay_ms(500);
			}
*/

		}

}
