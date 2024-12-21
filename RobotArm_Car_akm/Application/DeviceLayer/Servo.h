#ifndef __SERVO_H
#define __SERVO_H

#include "stm32f1xx_hal.h"
#include "tim.h"

#define MAX_DEGR_CCR																250
#define ARM_SERVO_UNIT															1
#define CHASSIS_SERVO_UNIT													3

#define BOTTOM_SERVO_MIDDLE_CCR							(uint16_t)142
#define BOTTOM_SERVO_LEFT_LIMIT_CCR					(uint16_t)102
#define BOTTOM_SERVO_RIGHT_LIMIT_CCR				(uint16_t)182

#define FRONT_SERVO_MIDDLE_CCR							(uint16_t)150
#define FRONT_SERVO_MAX_LIMIT_CCR						(uint16_t)200
#define FRONT_SERVO_MIN_LIMIT_CCR						(uint16_t)95

#define LEFT_SERVO_MIDDLE_CCR								(uint16_t)150
#define LEFT_SERVO_RISE_LIMIT_CCR						(uint16_t)215
#define LEFT_SERVO_DESCEND_LIMIT_CCR				(uint16_t)120

#define RIGHT_SERVO_MIDDLE_CCR							(uint16_t)170
#define RIGHT_SERVO_EXTEND_LIMIT_CCR				(uint16_t)230
#define RIGHT_SERVO_DRAWBACK_LIMIT_CCR			(uint16_t)140

typedef enum
{
	FRONT = 0,
	LEFT = 1,
	RIGHT = 2,
	BOTTOM = 3,
	NUM_OF_SERVO = 4
}servo_signal_e;

typedef struct
{
	uint16_t degr_CCR;
	
}servo_t;

void Servo_Init(servo_t* servo, servo_signal_e servo_signal);
void Servo_FRONT_Degr_Set(uint16_t degr_ccr);
void Servo_BOTTOM_Degr_Set(uint16_t degr_ccr);
void Servo_LEFT_Degr_Set(uint16_t degr_ccr);
void Servo_RIGHT_Degr_Set(uint16_t degr_ccr);

void Servo_BOTTOM_Start(servo_signal_e servo_signal);
void Servo_LEFT_Start(servo_signal_e servo_signal);
void Servo_RIGHT_Start(servo_signal_e servo_signal);
void Servo_FRONT_Start(servo_signal_e servo_signal);

#endif
