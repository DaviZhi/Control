#include "module_ctrl.h"
#include "stdlib.h"

module_t* Module;		//The whole module structure ptr

#ifdef 	ACKERMANN_CHASSIS
/**@brief Initialize module, including arm and chassis.
	*@note	This function will be called in main function.
	*@param None
  *@retval None
  */
void Module_Init(void)
{
	Module = (module_t*)malloc(sizeof(module_t));
	Module->arm = (arm_t*)malloc(sizeof(arm_t));
	Module->chassis = (chassis_t*)malloc(sizeof(chassis_t));
	Module->arm->arm_servo = (servo_t*)malloc(sizeof(servo_t) * 3);
	Module->chassis->chassis_info = (chassis_info_t*)malloc(sizeof(chassis_info_t));
	Module->chassis->chassis_motor = (motor_t*)malloc(sizeof(motor_t) * NUM_OF_WHEEL);
	Module->chassis->chassis_servo = (servo_t*)malloc(sizeof(servo_t) * 1);
	
	Chassis_Init(Module->chassis);
	Arm_Init(Module->arm);
}

/**@brief Deinitialize the whole module.
	*@param None
  *@retval None
  */
void Module_Deinit(void)
{
	if(Module != NULL)
	{
		free(Module->chassis->chassis_servo);
		free(Module->chassis->chassis_motor);
		free(Module->chassis->chassis_info);
		free(Module->arm->arm_servo);
		free(Module->chassis);
		free(Module->arm);
		
		free(Module);
	}
}

/**@brief Start the whole module.
	*@note	This function will be called in main function.
	*@param Whole module structure ptr
	*@param Remote structure ptr
  *@retval None
  */
void Module_Start(module_t* module, remote_t* remote)
{
	switch(remote->remote_info->key_info->MODE)		//Mode choice
	{
		case RED_MODE:
		{
			Chassis_RedMode_Ctrl_Start(module->chassis, remote);
			Arm_RedMode_Ctrl_Start(module->arm, remote);
			break;
		}
		
		case GREEN_MODE:
		{		//...debug
			break;
		}
		
		default:
			break;
	}
}

#elif defined MECANUM_CHASSIS
/*ADD YOUR CODE HERE*/

/*END YOUR CODE HERE*/

#endif
