#ifndef __MODULE_CTRL_H
#define __MODULE_CTRL_H

#include "remote.h"
#include "chassis.h"
#include "mechanical_arm.h"

/******************************Private structure******************************************/

typedef struct
{
	chassis_t* chassis;
	arm_t* arm;
	
}module_t;

extern module_t* Module;		//The whole module structure ptr

/******************************Private function******************************************/

void Module_Init(void);
void Module_Deinit(void);
void Module_Start(module_t* module, remote_t* remote);

#endif
