#define F_CPU 16000000UL
#include <avr/io.h>
#include "motor_pwm.c"
#include <util/delay.h>


void main(void)
{

int speed=50;
MOTOR_Init_Ports();
MOTOR_Init_Timer1_PWM();
MOTOR_Motor2_Set_PWMduty(40);
MOTOR_PWM_Motor2_Forward();
for(;;)
	{
		for(speed=50;speed<101;speed++)
		{	MOTOR_Motor2_Set_PWMduty(speed);
			_delay_ms(500);
		}/*MOTOR_Motor2_Set_PWMduty(80);
		_delay_ms(1000);
		MOTOR_Motor2_Set_PWMduty(100);
		_delay_ms(1000);
		MOTOR_Motor2_Set_PWMduty(20);
		_delay_ms(1000);
		MOTOR_Motor2_Set_PWMduty(40);
		_delay_ms(1000);

*/


	}

}
