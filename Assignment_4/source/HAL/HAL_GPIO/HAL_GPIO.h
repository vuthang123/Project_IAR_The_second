#ifndef HAL_GPIO_H
#define HAL_GPIO_H



#include "stdint.h"
#include "HAL_PORT.h"
#include "MKE16Z4.h"
typedef enum
{
	HAL_GPIO_SUCCESS = 0u,
	HAL_GPIO_FAIL
}HAL_GPIO_Erorr_E;

typedef enum
{	
	HAL_GPIO_INPUT = 0U,
	HAL_GPIO_OUTPUT
}HAL_GPIO_Select_Mode_IO;

/*******************************************************************************
 * API
 ******************************************************************************/
HAL_GPIO_Erorr_E HAL_GPIO_IO(FGPIO_Type* FGPIOx,uint32_t Pin_select,HAL_GPIO_Select_Mode_IO Select_Mode_IO);
uint32_t HAL_GPIO_Read_Pin(FGPIO_Type* FGPPIOx,uint32_t Pin_select);
void HAL_GPIO_Write_Pin(FGPIO_Type* GPIOx,FGPIO_Type* FGPIOy,uint32_t Pin_Select,uint8_t u8status);
HAL_GPIO_Erorr_E HAL_GPIO_Setup_Defaut(FGPIO_Type* GPIOx,uint32_t Pin_select);

HAL_GPIO_Erorr_E HAL_GPIO_Clear_State(FGPIO_Type* FGPIOy,uint32_t Pin_select);
 HAL_GPIO_Erorr_E HAL_GPIO_Set_State(FGPIO_Type* FGPIOx,uint32_t Pin_select);

#endif /*HAL_GPIO_H*/