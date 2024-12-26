#include "mechanical_arm.h"
#include "stdlib.h"

/**@brief Initialize servos on the arm to middle.
	*@param Arm structure ptr
  *@retval None
  */
void Arm_Init(arm_t* arm)
{
	Servo_Init(&arm->arm_servo[FRONT], FRONT);
	Servo_Init(&arm->arm_servo[LEFT], LEFT);
	Servo_Init(&arm->arm_servo[RIGHT], RIGHT);
}

/**@brief Deinitialize servos on the arm.
	*@param Arm structure ptr
  *@retval None
  */
void Arm_Deinit(arm_t* arm)
{
	if(arm != NULL)
	{
		free(arm->arm_servo);
		free(arm);
		
		arm = NULL;
	}
}

/**@brief Set control under red mode.
	*@param Arm structure ptr
	*@param Remote structure ptr
  *@retval None
  */
void Arm_RedMode_Ctrl_Set(arm_t* arm, remote_t* remote)
{
	RemoteKey_Info_Init(remote->remote_info->key_info);
	
	Arm_RightServo_Set(&arm->arm_servo[RIGHT], remote);
	Arm_LeftServo_Set(&arm->arm_servo[LEFT], remote);
	Arm_FrontServo_Set(&arm->arm_servo[FRONT], remote);
}

/**@brief Solve and set servo value.
	*@note	Solve servo that is on the right side.
	*@param Servo structure ptr
	*@param Remote structure ptr
  *@retval None
  */
void Arm_RightServo_Set(servo_t* servo, remote_t* remote)		//解算并获取CCR，传入角度设置函数中
{
	if(remote->remote_info->key_info->TRIANGLE == 0)
	{
		servo[RIGHT].degr_CCR += ARM_SERVO_UNIT;
		
		if(servo[RIGHT].degr_CCR > RIGHT_SERVO_EXTEND_LIMIT_CCR)
		{
			servo[RIGHT].degr_CCR = RIGHT_SERVO_EXTEND_LIMIT_CCR;
		}
		else if(servo[RIGHT].degr_CCR < RIGHT_SERVO_DRAWBACK_LIMIT_CCR)
		{
			servo[RIGHT].degr_CCR = RIGHT_SERVO_DRAWBACK_LIMIT_CCR;
		}
		Servo_RIGHT_Degr_Set(servo[RIGHT].degr_CCR);
	}
	
	if(remote->remote_info->key_info->FORK == 0)
	{
		servo[RIGHT].degr_CCR -= ARM_SERVO_UNIT;
		
		if(servo[RIGHT].degr_CCR > RIGHT_SERVO_EXTEND_LIMIT_CCR)
		{
			servo[RIGHT].degr_CCR = RIGHT_SERVO_EXTEND_LIMIT_CCR;
		}
		else if(servo[RIGHT].degr_CCR < RIGHT_SERVO_DRAWBACK_LIMIT_CCR)
		{
			servo[RIGHT].degr_CCR = RIGHT_SERVO_DRAWBACK_LIMIT_CCR;
		}
		Servo_RIGHT_Degr_Set(servo[RIGHT].degr_CCR);
	}
}

/**@brief Solve and set servo value.
	*@note	Solve servo that is on the left side.
	*@param Servo structure ptr
	*@param Remote structure ptr
  *@retval None
  */
void Arm_LeftServo_Set(servo_t* servo, remote_t* remote)
{
	if(remote->remote_info->key_info->SQUARE == 0)
	{
		servo[LEFT].degr_CCR += ARM_SERVO_UNIT;
		
		if(servo[LEFT].degr_CCR > LEFT_SERVO_RISE_LIMIT_CCR)
		{
			servo[LEFT].degr_CCR = LEFT_SERVO_RISE_LIMIT_CCR;
		}
		else if(servo[LEFT].degr_CCR < LEFT_SERVO_DESCEND_LIMIT_CCR)
		{
			servo[LEFT].degr_CCR = LEFT_SERVO_DESCEND_LIMIT_CCR;
		}
		Servo_LEFT_Degr_Set(servo[LEFT].degr_CCR);
	}
	
	if(remote->remote_info->key_info->CYCLE == 0)
	{
		servo[LEFT].degr_CCR -= ARM_SERVO_UNIT;
		
		if(servo[LEFT].degr_CCR > LEFT_SERVO_RISE_LIMIT_CCR)
		{
			servo[LEFT].degr_CCR = LEFT_SERVO_RISE_LIMIT_CCR;
		}
		else if(servo[LEFT].degr_CCR < LEFT_SERVO_DESCEND_LIMIT_CCR)
		{
			servo[LEFT].degr_CCR = LEFT_SERVO_DESCEND_LIMIT_CCR;
		}
		Servo_LEFT_Degr_Set(servo[LEFT].degr_CCR);
	}
}

/**@brief Solve and set servo value.
	*@note	Solve servo that is on the front side.
	*@param Servo structure ptr
	*@param Remote structure ptr
  *@retval None
  */
void Arm_FrontServo_Set(servo_t* servo, remote_t* remote)
{
	if(remote->remote_info->key_info->L2 == 0)
	{
		servo[FRONT].degr_CCR += ARM_SERVO_UNIT;
		
		if(servo[FRONT].degr_CCR > FRONT_SERVO_MAX_LIMIT_CCR)
		{
			servo[FRONT].degr_CCR = FRONT_SERVO_MAX_LIMIT_CCR;
		}
		else if(servo[FRONT].degr_CCR < FRONT_SERVO_MIN_LIMIT_CCR)
		{
			servo[FRONT].degr_CCR = FRONT_SERVO_MIN_LIMIT_CCR;
		}
		Servo_FRONT_Degr_Set(servo[FRONT].degr_CCR);
	}
	
	if(remote->remote_info->key_info->R2 == 0)
	{
		servo[FRONT].degr_CCR -= ARM_SERVO_UNIT;
		
		if(servo[FRONT].degr_CCR > FRONT_SERVO_MAX_LIMIT_CCR)
		{
			servo[FRONT].degr_CCR = FRONT_SERVO_MAX_LIMIT_CCR;
		}
		else if(servo[FRONT].degr_CCR < FRONT_SERVO_MIN_LIMIT_CCR)
		{
			servo[FRONT].degr_CCR = FRONT_SERVO_MIN_LIMIT_CCR;
		}
		Servo_FRONT_Degr_Set(servo[FRONT].degr_CCR);
	}
}

/**@brief Start control under red mode.
	*@param Arm structure ptr
	*@param Remote structure ptr
  *@retval None
  */
void Arm_RedMode_Ctrl_Start(arm_t* arm, remote_t* remote)
{
	Arm_RedMode_Ctrl_Set(arm, remote);		
	
	//先解算，再启动
	Servo_LEFT_Start(LEFT);
	Servo_RIGHT_Start(RIGHT);
//	Servo_FRONT_Start(FRONT);		//测试，要换一个新的舵机
}
