#ifndef __CHASSIS_H
#define __CHASSIS_H

#include "remote.h"
#include "Servo.h"
#include "motor.h"

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
	
}chassis_t;

void Chassis_Init(chassis_t* chassis);
void Chassis_Deinit(chassis_t* chassis);
void Chassis_RedMode_Ctrl_Set(chassis_t* chassis, remote_t* remote);
void Chassis_RedMode_Ctrl_Start(chassis_t* chassis, remote_t* remote);

#endif
