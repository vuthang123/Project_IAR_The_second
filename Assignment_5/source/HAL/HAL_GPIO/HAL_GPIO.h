#ifndef HAL_GPIO_H
#define HAL_GPIO_H



#include "stdint.h"
#include "HAL_PORT.h"
#include "MKE16Z4.h"
typedef enum
{
    HAL_GPIO_SUCCESS = 0u,
    HAL_GPIO_FAIL
}HALGPIO_Erorr_Code;

typedef enum
{    
    HAL_GPIO_INPUT = 0U,
    HAL_GPIO_OUTPUT
}HALGPIO_SelectMode_IO;

/*******************************************************************************
 * API
 ******************************************************************************/
HALGPIO_Erorr_Code HAL_GPIO_IO(FGPIO_Type* FGPIOx,uint32_t Pin_select,HALGPIO_SelectMode_IO Select_Mode_IO);
uint32_t HAL_GPIO_Read_Pin(FGPIO_Type* FGPPIOx,uint32_t Pin_select);
void HAL_GPIO_Write_Pin(FGPIO_Type* GPIOx,FGPIO_Type* FGPIOy,uint32_t Pin_Select,uint8_t u8status);
HALGPIO_Erorr_Code HAL_GPIO_Setup_Defaut(FGPIO_Type* GPIOx,uint32_t Pin_select);

HALGPIO_Erorr_Code HAL_GPIO_Clear_State(FGPIO_Type* FGPIOy,uint32_t Pin_select);
HALGPIO_Erorr_Code HAL_GPIO_Set_State(FGPIO_Type* FGPIOx,uint32_t Pin_select);

#endif /*HAL_GPIO_H*/