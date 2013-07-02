/*----------------------------------------------------------------
-----------------HEADER FILES-------------------------------------
-----------------------------------------------------------------*/

#include <avr/io.h>
#include "motor_pwm.h"

#define _BV(bit) (1 << (bit))

/*----------------------------------------------------------------
-------------CONNECTION BETWEEN MOTOR AND ATMEGA128-----------------
-----------------------------------------------------------------*/
#define MOTOR_PWM_DDR DDRB
#define MOTOR_PWM_PORT PORTB
#define MOTOR_PWM_OC1A 5
#define MOTOR_PWM_OC1B 6

#define MOTOR_DIR_DDR DDRB
#define MOTOR_DIR_PORT PORTB
#define MOTOR_DIR_MOTOR1_PIN1 1
#define MOTOR_DIR_MOTOR1_PIN2 0
#define MOTOR_DIR_MOTOR2_PIN1 3
#define MOTOR_DIR_MOTOR2_PIN2 2


/*----------------------------------------------------------------
------------FUNCTION TO SET THE PORT PINS TO OUTPUT MODE------------
-----------------TO SEND THE PWM SIGNALS AND DIRECTION CONTROL-------
-----------------------------------------------------------------*/

void MOTOR_Init_Ports(void)
{
MOTOR_PWM_DDR |= (_BV(MOTOR_PWM_OC1A)|_BV(MOTOR_PWM_OC1B));
//set the bit 5 and 6 for PWM pins PB5 (OC1A) & PB6 (OC1B) to make them outputs,
MOTOR_PWM_PORT &=~(_BV(MOTOR_PWM_OC1A)|_BV(MOTOR_PWM_OC1A));
//clear the 2 PWM pins at starting
MOTOR_DIR_DDR |=(_BV(MOTOR_DIR_MOTOR1_PIN1)|_BV(MOTOR_DIR_MOTOR1_PIN2)|_BV(MOTOR_DIR_MOTOR2_PIN1)|_BV(MOTOR_DIR_MOTOR2_PIN2));
//sets the motor direction control bits the make them as output pins
MOTOR_DIR_PORT &=~(_BV(MOTOR_DIR_MOTOR1_PIN1)|_BV(MOTOR_DIR_MOTOR1_PIN2)|_BV(MOTOR_DIR_MOTOR2_PIN1)|_BV(MOTOR_DIR_MOTOR2_PIN2));
// clears the 4 direction control pins at starting
}



/*----------------------------------------------------------------
------------FUNCTION TO SET THE PWM SIGNAL AT 10KHZ---------------
-----------------------------------------------------------------*/
void MOTOR_Init_Timer1_PWM(void)
{
TCNT1=0x0000; // intilize timer1 to zero
TCCR1A = 0b10100010;
// 10 for COM1A1 and COM1A0 - clear on compare match for OC1A(Non-inverting PWM),
// 10 for COM1B1 and COM1B0 - clear on compare match for OC1B(Non-inverting PWM)
// 00 for COM1C1 and COM1C0 - as we are not using OC1C
// 10 for WGM11 and WGM10 - to select PWM, phase correct mode of operation
TCCR1B = 0b00010010;
// 000 - not used
// 10 for WGM13 and WGM12 - to select PWM, phase correct mode of operation
// 010 for CS12, CS11 and CS10 to get clkIO/8 (From prescaler)
TCCR1C = 0b00000000; // do nothing
ICR1H = (100 >> 8); // f(PWM) = 16Mhz/2/8/100 = 10Khz

ICR1L = (100 & 0xFF); // decides the TOP value for the timer variable TCNT1
OCR1A = 0x0000; // decides when to change the High to Low on OC1A to change duty cycle
OCR1B = 0x0000;
// decides when to change the High to Low on OC1B to change duty cycle
// motor speed corresponds to duty cycle = ton/(ton + toff)
// ton/(ton + toff) = OCRnA/ICR1
}




/*----------------------------------------------------------------
------------FUNCTION TO Set speed of MOTOR1 -----------------------------
-----------------------------------------------------------------*/
void MOTOR_Motor1_Set_PWMduty(int pwmduty1) //
{
OCR1A = pwmduty1;
}
/*----------------------------------------------------------------
------------FUNCTION TO Set speed of MOTOR2 -----------------------------
-----------------------------------------------------------------*/
void MOTOR_Motor2_Set_PWMduty(int pwmduty2) //
{
OCR1B = pwmduty2;
}
/*----------------------------------------------------------------
------------FUNCTION TO STOP MOTOR1 -----------------------------
-----------------------------------------------------------------*/
void MOTOR_PWM_Motor1_Stop(void) //
{
MOTOR_DIR_PORT &=~(_BV(MOTOR_DIR_MOTOR1_PIN1)|_BV(MOTOR_DIR_MOTOR1_PIN2));
// clears the direction bits
}
/*----------------------------------------------------------------
------------FUNCTION TO RUN MOTOR1 IN FORWARD DIRECTION -----------
-----------------------------------------------------------------*/
void MOTOR_PWM_Motor1_Forward(void) //
{
MOTOR_DIR_PORT &=~(_BV(MOTOR_DIR_MOTOR1_PIN1)|_BV(MOTOR_DIR_MOTOR1_PIN2));

// clears the direction bits
MOTOR_DIR_PORT |= (_BV(MOTOR_DIR_MOTOR1_PIN1));// sets PIN1
MOTOR_DIR_PORT &=~(_BV(MOTOR_DIR_MOTOR1_PIN2)) ; // clears PIN2
}
/*----------------------------------------------------------------
------------FUNCTION TO RUN MOTOR1 IN BACKWARD DIRECTION ----------
-----------------------------------------------------------------*/
void MOTOR_PWM_Motor1_Backward(void) //
{
MOTOR_DIR_PORT &=~(_BV(MOTOR_DIR_MOTOR1_PIN1)|_BV(MOTOR_DIR_MOTOR1_PIN2));
// clears the direction bits
MOTOR_DIR_PORT &=~(_BV(MOTOR_DIR_MOTOR1_PIN1)) ; // clears PIN1
MOTOR_DIR_PORT |= (_BV(MOTOR_DIR_MOTOR1_PIN2));// sets PIN2
}
/*----------------------------------------------------------------
------------FUNCTION TO STOP MOTOR2 -----------------------------
-----------------------------------------------------------------*/
void MOTOR_PWM_Motor2_Stop(void) //
{
MOTOR_DIR_PORT &=~(_BV(MOTOR_DIR_MOTOR2_PIN1)|_BV(MOTOR_DIR_MOTOR2_PIN2));
// clears the direction bits
}
/*----------------------------------------------------------------
------------FUNCTION TO RUN MOTOR2 IN FORWARD DIRECTION -----------
-----------------------------------------------------------------*/
void MOTOR_PWM_Motor2_Forward(void) //
{
MOTOR_DIR_PORT &=~(_BV(MOTOR_DIR_MOTOR2_PIN1)|_BV(MOTOR_DIR_MOTOR2_PIN2));
// clears the direction bits
MOTOR_DIR_PORT &=~(_BV(MOTOR_DIR_MOTOR2_PIN1)) ; // clears PIN1
MOTOR_DIR_PORT |= (_BV(MOTOR_DIR_MOTOR2_PIN2));// sets PIN2
}
/*----------------------------------------------------------------
------------FUNCTION TO RUN MOTOR2 IN BACKWARD DIRECTION ----------
-----------------------------------------------------------------*/
void MOTOR_PWM_Motor2_Backward(void) //
{
MOTOR_DIR_PORT &=~(_BV(MOTOR_DIR_MOTOR2_PIN1)|_BV(MOTOR_DIR_MOTOR2_PIN2));
// clears the direction bits
MOTOR_DIR_PORT |= (_BV(MOTOR_DIR_MOTOR2_PIN1));// sets PIN1
MOTOR_DIR_PORT &=~(_BV(MOTOR_DIR_MOTOR2_PIN2)) ; // clears PIN2
}
/*----------------------------------------------------------------
------------FUNCTION TO STOP ROBOT
-----------------------------------------------------------------*/
void ROBOT_Stop(void) //
{
MOTOR_PWM_Motor1_Stop();
MOTOR_PWM_Motor2_Stop();
}
/*----------------------------------------------------------------
------------FUNCTION TO RUN ROBOT backwards
-----------------------------------------------------------------*/
void ROBOT_Backward(void) //
{
MOTOR_PWM_Motor1_Backward();
MOTOR_PWM_Motor2_Backward();
}
/*----------------------------------------------------------------
------------FUNCTION TO RUN ROBOT forwards
-----------------------------------------------------------------*/
void ROBOT_Forward(void) //
{
MOTOR_PWM_Motor1_Forward();
MOTOR_PWM_Motor2_Forward();
}
/*----------------------------------------------------------------
------------FUNCTION TO make ROBOT turn sharp left about centre point
-----------------------------------------------------------------*/
void ROBOT_Left_Centrepoint(void) //
{
MOTOR_PWM_Motor1_Backward();
MOTOR_PWM_Motor2_Forward();
}
/*----------------------------------------------------------------

------------FUNCTION TO make ROBOT turn slow left about left point
-----------------------------------------------------------------*/
void ROBOT_Left_Leftpoint(void) //
{
MOTOR_PWM_Motor1_Stop();
MOTOR_PWM_Motor2_Forward();
}
/*----------------------------------------------------------------
------------FUNCTION TO make ROBOT turn sharp right about centre point
-----------------------------------------------------------------*/
void ROBOT_Right_Centrepoint(void) //
{
MOTOR_PWM_Motor1_Forward();
MOTOR_PWM_Motor2_Backward();
}
/*----------------------------------------------------------------
------------FUNCTION TO make ROBOT turn slow right about right point
-----------------------------------------------------------------*/
void ROBOT_Right_Rightpoint(void) //
{
MOTOR_PWM_Motor1_Forward();
MOTOR_PWM_Motor2_Stop();
}


