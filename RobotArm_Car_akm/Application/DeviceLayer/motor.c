#include "motor.h"

/**@brief Initialize all four motors' revolution value to zero.
  *@param Motor structure ptr
  *@retval None
  */
void Motor_Init(motor_t* motor)
{
	for(uint8_t i = 0; i < NUM_OF_WHEEL; i++)
	{
		motor[i].rev_CCR = 0;
		motor[i].rev_state = REV_ZERO;
	}
}

/**@brief Set backward rev value of each motor.
  *@param Motor structure ptr
  *@param Flag that decides direction 
	*@param CCR
  *@retval None
  */
void Motor_Rev_backwardToRightOrLeft_Set(motor_t* motor, uint8_t dir_flag, uint16_t rev_ccr)
{
	for(uint8_t i = 0; i < NUM_OF_WHEEL; i++)
	{
		motor[i].rev_CCR = rev_ccr;
		motor[i].rev_state = REV_BACKWARD;
	}
	
	switch(dir_flag)
	{
		case 0:				//right
		{
			__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_4, motor[RB].rev_CCR - 400);		
			__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, motor[LB].rev_CCR);		
			__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_2, motor[RF].rev_CCR - 400);		
			__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_4, motor[LF].rev_CCR);		
			break;
		}
		case 1:				//left
		{
			__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_4, motor[RB].rev_CCR);		
			__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, motor[LB].rev_CCR - 400);		
			__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_2, motor[RF].rev_CCR);		
			__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_4, motor[LF].rev_CCR - 400);		
			break;
		}
		case 2:				//backward
		{
			__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_4, motor[RB].rev_CCR);		
			__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, motor[LB].rev_CCR);		
			__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_2, motor[RF].rev_CCR);		
			__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_4, motor[LF].rev_CCR);		
			break;
		}
		default:
			break;
	}
}

/**@brief Set forward rev value of each motor.
  *@param Motor structure ptr
  *@param Flag that decides direction 
	*@param CCR
  *@retval None
  */
void Motor_Rev_forwardToRightOrLeft_Set(motor_t* motor, uint8_t dir_flag, uint16_t rev_ccr)
{
	for(uint8_t i = 0; i < NUM_OF_WHEEL; i++)
	{
		motor[i].rev_CCR = rev_ccr;
		motor[i].rev_state = REV_FORWARD;
	}
	
	switch(dir_flag)
	{
		case 0:				//right
		{
			__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3, motor[RB].rev_CCR - 400);		
			__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, motor[LB].rev_CCR);		
			__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, motor[RF].rev_CCR - 400);		
			__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_3, motor[LF].rev_CCR);		
			break;
		}
		case 1:				//left
		{
			__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3, motor[RB].rev_CCR);		
			__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, motor[LB].rev_CCR - 400);		
			__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, motor[RF].rev_CCR);		
			__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_3, motor[LF].rev_CCR - 400);		
			break;
		}
		case 2:				//forward
		{
			__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3, motor[RB].rev_CCR);		
			__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, motor[LB].rev_CCR);		
			__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, motor[RF].rev_CCR);		
			__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_3, motor[LF].rev_CCR);		
			break;
		}
		default:
			break;
	}
	
}

/**@brief Set rev to zero of each motor.
  *@param Motor structure ptr
  *@retval None
  */
void Motor_Rev_Zero_Set(motor_t* motor)
{
	for(uint8_t i = 0; i < NUM_OF_WHEEL; i++)
	{
		motor[i].rev_CCR = 0;
		motor[i].rev_state = REV_ZERO;
	}
	
	__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3, motor[RB].rev_CCR);		
	__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, motor[LB].rev_CCR);		
	__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, motor[RF].rev_CCR);		
	__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_3, motor[LF].rev_CCR);		
}

/**@brief Start forward rev value of each motor.
  *@param None
  *@retval None
  */
void Motor_Rev_Forward_Start(void)
{
		HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3);
		HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
		HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_1);
		HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_3);
}

/**@brief Start backward rev value of each motor.
  *@param None
  *@retval None
  */
void Motor_Rev_Backward_Start(void)
{
		HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_4);
		HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);
		HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_2);
		HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_4);
}

/**@brief Stop backward rev value of each motor.
  *@param None
  *@retval None
  */
void Motor_Rev_Backward_Stop(void)
{
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_RESET);
	
	HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_4);
	HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_2);
	HAL_TIM_PWM_Stop(&htim4, TIM_CHANNEL_2);
	HAL_TIM_PWM_Stop(&htim4, TIM_CHANNEL_4);
}

/**@brief Stop forward rev value of each motor.
  *@param None
  *@retval None
  */
void Motor_Rev_Forward_Stop(void)
{
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_RESET);
	
	HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_3);
	HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_1);
	HAL_TIM_PWM_Stop(&htim4, TIM_CHANNEL_1);
	HAL_TIM_PWM_Stop(&htim4, TIM_CHANNEL_3);
}
