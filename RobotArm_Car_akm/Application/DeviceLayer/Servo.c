#include "Servo.h"

/**@brief Initialize all four servos to middle.
	*@param None
  *@retval None
  */
void Servo_Init(servo_t* servo, servo_signal_e servo_signal)
{
	switch(servo_signal)
	{
		case FRONT:
		{
			servo[FRONT].degr_CCR = FRONT_SERVO_MIDDLE_CCR;
			break;
		}
		case LEFT:
		{
			servo[LEFT].degr_CCR = LEFT_SERVO_MIDDLE_CCR;
			break;
		}
		case RIGHT:
		{
			servo[RIGHT].degr_CCR = RIGHT_SERVO_MIDDLE_CCR;
			break;
		}
		case BOTTOM:
		{
			servo[BOTTOM].degr_CCR = BOTTOM_SERVO_MIDDLE_CCR;
			break;
		}
		default:
			break;
	}
}

void Servo_FRONT_Degr_Set(uint16_t degr_ccr)
{
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, degr_ccr);
}

void Servo_BOTTOM_Degr_Set(uint16_t degr_ccr)
{
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, degr_ccr);
}

void Servo_LEFT_Degr_Set(uint16_t degr_ccr)
{
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, degr_ccr);
}

void Servo_RIGHT_Degr_Set(uint16_t degr_ccr)
{
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, degr_ccr);
}

void Servo_BOTTOM_Start(servo_signal_e servo_signal)
{
	if(servo_signal == BOTTOM)
	{
		HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_4);
	}
}

void Servo_LEFT_Start(servo_signal_e servo_signal)
{
	if(servo_signal == LEFT)
	{
		HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);
	}
}

void Servo_RIGHT_Start(servo_signal_e servo_signal)
{
	if(servo_signal == RIGHT)
	{
		HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);
	}
}

void Servo_FRONT_Start(servo_signal_e servo_signal)
{
	if(servo_signal == FRONT)
	{
		HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
	}
}
