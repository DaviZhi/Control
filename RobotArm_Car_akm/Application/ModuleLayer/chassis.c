#include "chassis.h"
#include "stdlib.h"

/**@brief Initialize motor and servo on the chassis to middle.
	*@param Chassis structure ptr
  *@retval None
  */
void Chassis_Init(chassis_t* chassis)
{
	Servo_Init(&chassis->chassis_servo[BOTTOM], BOTTOM);
	Motor_Init(chassis->chassis_motor);
}

/**@brief Deinitialize motor and servo on the chassis.
	*@param Chassis structure ptr
  *@retval None
  */
void Chassis_Deinit(chassis_t* chassis)
{
	if(chassis != NULL)
	{
		free(chassis->chassis_servo);
		free(chassis->chassis_motor);
		free(chassis->chassis_info);
		free(chassis);
		
		chassis = NULL;
	}
}

void Chassis_StickCtrl_Mode_Set(chassis_t* chassis)
{
	uint16_t correct = BOTTOM_SERVO_MIDDLE_CCR - PSS_X_MID;		//obtain offset
	
	RemoteJoystick_Info_Init(Remote->remote_info->joystick_info);
			
	if(Remote->remote_info->joystick_info->PSS_LY <= PSS_Y_MID)
	{
		//position limit
		if(Remote->remote_info->joystick_info->PSS_LY < PSS_Y_UP_LIMIT)
		{
			Remote->remote_info->joystick_info->PSS_LY = PSS_Y_UP_LIMIT;
		}
		
		chassis->chassis_info->Y_scale_factor = 
		MAX_REV_CCR / (PSS_Y_MID - PSS_Y_UP_LIMIT);		//8
		
		chassis->chassis_info->joystick_rev_CCR =	
		chassis->chassis_info->Y_scale_factor * (PSS_Y_MID - Remote->remote_info->joystick_info->PSS_LY);
	}
	
	else if(Remote->remote_info->joystick_info->PSS_LY > PSS_Y_MID)
	{
		//position limit
		if(Remote->remote_info->joystick_info->PSS_LY > PSS_Y_DOWN_LIMIT)
		{
			Remote->remote_info->joystick_info->PSS_LY = PSS_Y_DOWN_LIMIT;
		}
		
		chassis->chassis_info->Y_scale_factor = 
		MAX_REV_CCR / (PSS_Y_DOWN_LIMIT - PSS_Y_MID);		//8
		
		chassis->chassis_info->joystick_rev_CCR = 
		chassis->chassis_info->Y_scale_factor * (Remote->remote_info->joystick_info->PSS_LY - PSS_Y_MID);
		
//		Motor_Rev_Backward_Set(chassis->chassis_motor, chassis->chassis_info->joystick_rev_CCR);
	}
	
	chassis->chassis_info->X_scale_factor = 
	MAX_DEGR_CCR / (PSS_X_RIGHT_LIMIT - PSS_X_LEFT_LIMIT);		//1
	
	//median correction
	if(Remote->remote_info->joystick_info->PSS_RX < (BOTTOM_SERVO_LEFT_LIMIT_CCR - correct))
	{
		Remote->remote_info->joystick_info->PSS_RX = BOTTOM_SERVO_LEFT_LIMIT_CCR - correct;
	}
	if(Remote->remote_info->joystick_info->PSS_RX > (BOTTOM_SERVO_RIGHT_LIMIT_CCR - correct))
	{
		Remote->remote_info->joystick_info->PSS_RX = BOTTOM_SERVO_RIGHT_LIMIT_CCR - correct;
	}
	
	chassis->chassis_servo[BOTTOM].degr_CCR = 
	chassis->chassis_info->X_scale_factor * (Remote->remote_info->joystick_info->PSS_RX + correct);
	
	Servo_BOTTOM_Degr_Set(chassis->chassis_servo[BOTTOM].degr_CCR);
}

/**@brief Set control under red mode.
	*@param Chassis structure ptr
  *@retval None
  */
void Chassis_RedMode_Ctrl_Set(chassis_t* chassis, remote_t* remote)
{
	RemoteKey_Info_Init(remote->remote_info->key_info);		//获取遥控器的信息

	chassis->chassis_info->key_rev_CCR = KEY_REV_CCR;			//fixed rev

	if(remote->remote_info->key_info->UP == 0)		//若前进键按下
	{
		if(remote->remote_info->key_info->DOWN != 0)
		{
			Motor_Rev_Forward_Set(chassis->chassis_motor, chassis->chassis_info->key_rev_CCR);
		}
	}
	else if(remote->remote_info->key_info->UP == 1)		//否则停止正转
	{
		Motor_Rev_Forward_Stop();
	}
	if(remote->remote_info->key_info->DOWN == 0)		//若后退键按下，则电机反转
	{
		if(remote->remote_info->key_info->UP != 0)
		{
			Motor_Rev_Backward_Set(chassis->chassis_motor, chassis->chassis_info->key_rev_CCR);
		}
	}
	else if(remote->remote_info->key_info->DOWN == 1)		//否则停止反转
	{
		Motor_Rev_Backward_Stop();
	}
	
	//如果前进和后退键都按下了或者前进和后退都没按下，那么设置电机转速为0
	if((remote->remote_info->key_info->UP == 0 && remote->remote_info->key_info->DOWN == 0) || 
		(remote->remote_info->key_info->UP == 1 && remote->remote_info->key_info->DOWN == 1))
	{
		Motor_Rev_Zero_Set(chassis->chassis_motor);
	}
	
			if(remote->remote_info->key_info->R1 == 0)
			{
				chassis->chassis_servo[BOTTOM].degr_CCR += CHASSIS_SERVO_UNIT;
				if(chassis->chassis_servo[BOTTOM].degr_CCR > BOTTOM_SERVO_RIGHT_LIMIT_CCR)
				{
					chassis->chassis_servo[BOTTOM].degr_CCR = BOTTOM_SERVO_RIGHT_LIMIT_CCR;
				}
				else if(chassis->chassis_servo[BOTTOM].degr_CCR < BOTTOM_SERVO_LEFT_LIMIT_CCR)
				{
					chassis->chassis_servo[BOTTOM].degr_CCR = BOTTOM_SERVO_LEFT_LIMIT_CCR;
				}
				Servo_BOTTOM_Degr_Set(chassis->chassis_servo[BOTTOM].degr_CCR);
			}
			if(remote->remote_info->key_info->L1 == 0)
			{
				chassis->chassis_servo[BOTTOM].degr_CCR -= CHASSIS_SERVO_UNIT;
				if(chassis->chassis_servo[BOTTOM].degr_CCR > BOTTOM_SERVO_RIGHT_LIMIT_CCR)
				{
					chassis->chassis_servo[BOTTOM].degr_CCR = BOTTOM_SERVO_RIGHT_LIMIT_CCR;
				}
				else if(chassis->chassis_servo[BOTTOM].degr_CCR < BOTTOM_SERVO_LEFT_LIMIT_CCR)
				{
					chassis->chassis_servo[BOTTOM].degr_CCR = BOTTOM_SERVO_LEFT_LIMIT_CCR;
				}
				Servo_BOTTOM_Degr_Set(chassis->chassis_servo[BOTTOM].degr_CCR);
			}
			
			if(remote->remote_info->key_info->R1 != 0 && remote->remote_info->key_info->L1 != 0)
			{
				chassis->chassis_servo[BOTTOM].degr_CCR = BOTTOM_SERVO_MIDDLE_CCR;
				Servo_BOTTOM_Degr_Set(chassis->chassis_servo[BOTTOM].degr_CCR);
			}
}

/**@brief Start control under red mode.
	*@param Chassis structure ptr
  *@retval None
  */
void Chassis_RedMode_Ctrl_Start(chassis_t* chassis, remote_t* remote)
{
	Chassis_RedMode_Ctrl_Set(chassis, remote);		//先将按键控制下的值解算完成
	Servo_BOTTOM_Start(BOTTOM);
	
	if(chassis->chassis_motor->rev_state == REV_BACKWARD)
	{
		Motor_Rev_Backward_Start();
	}
	else if(chassis->chassis_motor->rev_state == REV_FORWARD)
	{
		Motor_Rev_Forward_Start();
	}
}
