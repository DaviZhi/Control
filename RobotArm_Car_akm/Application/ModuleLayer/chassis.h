#ifndef __CHASSIS_H
#define __CHASSIS_H

#include "remote.h"
#include "Servo.h"
#include "motor.h"

/******************************Private define******************************************/

#define		LEFT_FLAG				1
#define 	RIGHT_FLAG			0
#define		STRAIGHT_FLAG		2

/*Choose which type of chassis should be used*/
#define		ACKERMANN_CHASSIS
//#define		MECANUM_CHASSIS

/******************************Private structure******************************************/

typedef struct
{
	uint16_t key_rev_CCR;
	uint16_t joystick_rev_CCR;
	uint16_t X_scale_factor;
	uint16_t Y_scale_factor;
	
}chassis_info_t;

typedef struct
{
	chassis_info_t* chassis_info;
	motor_t* chassis_motor;
	servo_t* chassis_servo;
	uint8_t chassis_dirFlag;
}chassis_t;

/******************************Private function******************************************/

void Chassis_Init(chassis_t* chassis);
void Chassis_Deinit(chassis_t* chassis);
void Chassis_RedMode_Ctrl_Set(chassis_t* chassis, remote_t* remote);
void Chassis_RedMode_Ctrl_Start(chassis_t* chassis, remote_t* remote);

#endif
