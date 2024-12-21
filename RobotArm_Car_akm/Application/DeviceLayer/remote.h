#ifndef __REMOTE_H
#define __REMOTE_H

#include "stm32f1xx_hal.h"
#include "spi.h"
#include "tim.h"

/******************************Private Define**********************************************/

#define 		PSS_X_LEFT_LIMIT				(uint8_t)0x03			//3
#define 		PSS_X_RIGHT_LIMIT				(uint8_t)0xFD			//253
#define 		PSS_Y_UP_LIMIT					(uint8_t)0x02			//2
#define 		PSS_Y_DOWN_LIMIT				(uint8_t)0xFC			//252
#define 		PSS_X_MID	   						(uint8_t)0X80			//128
#define 		PSS_Y_MID     					(uint8_t)0X7F			//127

/**@brief Mode switch of remote control.
  */
#define			RED_MODE								(uint8_t)0x73
#define			GREEN_MODE							(uint8_t)0x41

#define			CMD_START								(uint8_t)0x01
#define			REQUEST_DATA						(uint8_t)0x42
#define			SEND_START_FLAG					(uint8_t)0x5A
#define			COMMUNI_CYCLE_LENGTH		(uint8_t)0x09

#define			KEY_REV_CCR							(uint16_t)999		//rev_ccr when key is pressed

/******************************Private Structure******************************************/

/**@brief Map every key on remote control.
  */
typedef struct
{
	uint8_t SELECT;
	uint8_t L3;			//press left joystick
	uint8_t R3;			//press right joystick
	uint8_t START;
	uint8_t UP;
	uint8_t RIGHT;
	uint8_t DOWN;
	uint8_t LEFT;
	uint8_t L2;
	uint8_t R2;
	uint8_t L1;
	uint8_t R1;
	uint8_t CYCLE;
	uint8_t FORK;
	uint8_t SQUARE;
	uint8_t TRIANGLE;
	uint8_t MODE;
	
}key_info_t;

typedef struct
{
	uint8_t PSS_RX;
	uint8_t PSS_RY;
	uint8_t PSS_LX;
	uint8_t PSS_LY;
	
}joystick_info_t;

typedef struct
{
	joystick_info_t* joystick_info;
	key_info_t* key_info;
	
}remote_info_t;

typedef struct
{
	remote_info_t* remote_info;
	
}remote_t;

extern remote_t* Remote;

void Remote_Init(void);
void Remote_Communi_Start(remote_t* remote);
void RemoteKey_Info_Init(key_info_t* key_info);
void RemoteJoystick_Info_Init(joystick_info_t* joystick_info);
void Remote_Info_Init(remote_info_t* remote_info);
void Delay_us(uint16_t nus);

#endif
