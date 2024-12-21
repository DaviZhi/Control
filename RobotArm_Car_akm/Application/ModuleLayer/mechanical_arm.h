#ifndef __MECHANICAL_ARM_H
#define __MECHANICAL_ARM_H

#include "Servo.h"
#include "remote.h"

#define			SCALE_FACTOR			1

typedef struct
{
	servo_t* arm_servo;
	
}arm_t;

void Arm_Init(arm_t* arm);
void Arm_Deinit(arm_t* arm);
void Arm_RightServo_Set(servo_t* servo, remote_t* remote);
void Arm_LeftServo_Set(servo_t* servo, remote_t* remote);
void Arm_FrontServo_Set(servo_t* servo, remote_t* remote);
void Arm_RedMode_Ctrl_Set(arm_t* arm, remote_t* remote);
void Arm_RedMode_Ctrl_Start(arm_t* arm, remote_t* remote);

#endif
