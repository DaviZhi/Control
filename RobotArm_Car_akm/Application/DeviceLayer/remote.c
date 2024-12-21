#include "remote.h" 
#include "stdlib.h"

remote_t* Remote;		//Ò£¿ØÆ÷Ö¸Õë

uint8_t Rx_Data[COMMUNI_CYCLE_LENGTH] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
uint8_t remote_cmd[3] = {CMD_START, REQUEST_DATA, 0x00};

/**@brief Initialize remote structure.
	*@note	Assign address.
	*@param None
  *@retval None
  */
void Remote_Init(void)
{
	static joystick_info_t joystick_info = {PSS_X_MID, PSS_Y_MID, PSS_X_MID, PSS_Y_MID};
	static key_info_t key_info = {1, 1, 1, 1, 1, 1 ,1, 1, 1, 1, 1, 1 ,1, 1, 1, 1, 1};
	static remote_info_t remote_info = {&joystick_info, &key_info};
	static remote_t remote = {&remote_info};
	Remote = &remote;

//	remote = (remote_t*)malloc(sizeof(remote_t));
//	remote->remote_info = (remote_info_t*)malloc(sizeof(remote_info_t));
//	remote->remote_info->joystick_info = (joystick_info_t*)malloc(sizeof(joystick_info_t));
//	remote->remote_info->key_info = (key_info_t*)malloc(sizeof(key_info_t));
}

/**@brief Remote start communication.
	*@note	This function will be called by upper layer.
	*@param Remote control structure ptr
  *@retval None
  */
void Remote_Communi_Start(remote_t* remote)		
{
	HAL_GPIO_WritePin(GPIOA, SPI_CS_Pin, GPIO_PIN_RESET);
	
	HAL_SPI_TransmitReceive(&hspi1, &remote_cmd[0], &Rx_Data[0], 1, 0xFFFF);
	Delay_us(18);
	HAL_SPI_TransmitReceive(&hspi1, &remote_cmd[1], &Rx_Data[1], 1, 0xFFFF);
	Delay_us(18);
	HAL_SPI_TransmitReceive(&hspi1, &remote_cmd[2], &Rx_Data[2], 1, 0xFFFF);
	Delay_us(18);
	
	for(uint8_t i = 3; i < 9; i++)
	{
		HAL_SPI_TransmitReceive(&hspi1, &remote_cmd[2], &Rx_Data[i], 1, 0xFFFF);
		
		//Assign values to each key and transfer the joystick simulation values into the structure
		Remote_Info_Init(remote->remote_info);		
		
		Delay_us(18);
	}
	
	HAL_GPIO_WritePin(GPIOA, SPI_CS_Pin, GPIO_PIN_SET);
	Delay_us(5000);
}

/**@brief Initialize key info of remote control, 
	*@note	Map every key value on the remote control to the structure.
	*@param Key info structure ptr
  *@retval None
  */
void RemoteKey_Info_Init(key_info_t* key_info)		
{
	key_info->MODE = Rx_Data[1];
	key_info->LEFT = (Rx_Data[3] >> 7) & 0x01;
	key_info->DOWN = (Rx_Data[3] >> 6) & 0x01;
	key_info->RIGHT = (Rx_Data[3] >> 5) & 0x01;
	key_info->UP = (Rx_Data[3] >> 4) & 0x01;
	key_info->START = (Rx_Data[3] >> 3) & 0x01;
	key_info->R3 = (Rx_Data[3] >> 2) & 0x01;
	key_info->L3 = (Rx_Data[3] >> 1) & 0x01;
	key_info->SELECT = Rx_Data[3] & 0x01;
	key_info->SQUARE = (Rx_Data[4] >> 7) & 0x01;
	key_info->FORK = (Rx_Data[4] >> 6) & 0x01;
	key_info->CYCLE = (Rx_Data[4] >> 5) & 0x01;
	key_info->TRIANGLE = (Rx_Data[4] >> 4) & 0x01;
	key_info->R1 = (Rx_Data[4] >> 3) & 0x01;
	key_info->L1 = (Rx_Data[4] >> 2) & 0x01;
	key_info->R2 = (Rx_Data[4] >> 1) & 0x01;
	key_info->L2 = Rx_Data[4] & 0x01;
}

/**@brief Initialize joystick info of remote control.
	*@param Joystick info structure ptr.
  *@retval None
  */
void RemoteJoystick_Info_Init(joystick_info_t* joystick_info)
{
	joystick_info->PSS_RX = Rx_Data[5];
	joystick_info->PSS_RY = Rx_Data[6];
	joystick_info->PSS_LX = Rx_Data[7];
	joystick_info->PSS_LY = Rx_Data[8];
}

/**@brief Initialize remote control info.
	*@param remote control info structure ptr.
  *@retval None
  */
void Remote_Info_Init(remote_info_t* remote_info)
{
	RemoteKey_Info_Init(remote_info->key_info);
	RemoteJoystick_Info_Init(remote_info->joystick_info);
}

/**@brief A microsecond level delay function.
	*@param Delay time. 
  *@retval None
  */
void Delay_us(uint16_t nus)
{
	__HAL_TIM_SET_COUNTER(&htim1, 0);
	__HAL_TIM_ENABLE(&htim1);
	while(__HAL_TIM_GET_COUNTER(&htim1) < nus);
	__HAL_TIM_DISABLE(&htim1);
}
