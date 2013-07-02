#ifndef __MOTOR_PWM__
#define __MOTOR_PWM__
/*----------------------------------------------------------------
-----------------FUNCTIONS PROTOTYPES-----------------------------
-----------------------------------------------------------------*/
void MOTOR_Init_Ports(void);
// TO SET THE PORT PINS TO OUTPUT MODE
void MOTOR_Init_Timer1_PWM(void); // TO SET THE PWM SIGNAL AT 10KHZ
void MOTOR_Motor1_Set_PWMduty(int pwmduty1); //TO Set speed of MOTOR1
void MOTOR_Motor2_Set_PWMduty(int pwmduty2); // TO Set speed of MOTOR2
void MOTOR_PWM_Motor1_Stop(void); // TO STOP MOTOR1
void MOTOR_PWM_Motor1_Forward(void); // TO RUN MOTOR1 IN FORWARD DIRECTION
void MOTOR_PWM_Motor1_Backward(void); // TO RUN MOTOR1 IN BACKWARD DIRECTION
void MOTOR_PWM_Motor2_Stop(void); // TO STOP MOTOR2
void MOTOR_PWM_Motor2_Forward(void); // TO RUN MOTOR2 IN FORWARD DIRECTION
void MOTOR_PWM_Motor2_Backward(void); // TO RUN MOTOR2 IN BACKWARD DIRECTION
void ROBOT_Backward(void); // TO RUN ROBOT backwards
void ROBOT_Forward(void); // TO RUN ROBOT forwards
void ROBOT_Left_Centrepoint(void); // TO make ROBOT turn sharp left about centre point
void ROBOT_Left_Leftpoint(void); // TO make ROBOT turn slow left about left point
void ROBOT_Right_Centrepoint(void); // TO make ROBOT turn sharp right about centre point
void ROBOT_Right_Rightpoint(void); // TO make ROBOT turn slow right about right point
void ROBOT_Stop(void); // to make robot stop
#endif

