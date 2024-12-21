#ifndef __MOTOR_H
#define __MOTOR_H

#include "stm32f1xx_hal.h"
#include "tim.h"

#define MAX_REV_CCR		1000
#define REV_FORWARD		1
#define REV_BACKWARD	2
#define REV_ZERO			0

/*Position of each motor*/
typedef enum
{
	RF = 0,		//right front
	LF = 1,		//left front
	LB = 2,		//left behind
	RB = 3,		//right behind
	NUM_OF_WHEEL = 4,
	
}motor_signal_e;

typedef struct
{
	uint16_t rev_CCR;		//revolution speed(actual value of CCR)
	uint8_t rev_state;
	
}motor_t;

void Motor_Init(motor_t* motor);
void Motor_Rev_Forward_Set(motor_t* motor, uint16_t rev_ccr);
void Motor_Rev_Backward_Set(motor_t* motor, uint16_t rev_ccr);
void Motor_Rev_Zero_Set(motor_t* motor);
void Motor_Rev_Forward_Start(void);
void Motor_Rev_Backward_Start(void);
void Motor_Rev_Backward_Stop(void);
void Motor_Rev_Forward_Stop(void);

#endif
