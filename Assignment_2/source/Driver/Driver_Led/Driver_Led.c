#include "Driver_Led.h"

#include "HAL_PORT.h"

#include "HAL_CLOCK.h"


/*******************************************************************************
 * Variables 
 ******************************************************************************/
uint8_t u8status = 0;


/*******************************************************************************
 * Code
 ******************************************************************************/

/**
  * @brief  Initialization for led
  * @param  FGPIO_Type  FGPIOx (FGPIOA ,FGPIOB,FGPIOC,FGPIOD,FGPIOE) for led 	    
  *	@retval 0 : SUCCESS
			1 : ERROR
  */

DRIVER_LED_Erorr DRIVER_LED_init(PORT_Type* PORTx)
{
	
	DRIVER_LED_Erorr E_Retval = DRIVER_LED_SUCCESS ;
	/*cHECK ENABLE CLOCK PORT  B*/
	if (HAL_CLOCK_Init(PCC_PORTB_INDEX,PCC_PORTB_CGC) != 0)
	{
		E_Retval = DRIVER_LED_FAIL;	
	}
	/*select mode gpio*/
	if(HAL_PORT_Select_Mode(PORTx,LED_RED,Mode_Gpio) != 0)
	{
		E_Retval = DRIVER_LED_FAIL;	
	}
	/*config output*/
	if(HAL_GPIO_IO(FGPIOB,LED_RED1,HAL_GPIO_OUTPUT))
	{
		E_Retval = DRIVER_LED_FAIL;	
	}
	/*Setup defaut*/
	if(HAL_GPIO_Setup_Defaut(FGPIOB,LED_RED1))
	{
		E_Retval = DRIVER_LED_FAIL;	
	}
	return E_Retval;
}

/**
  * @brief  Initialization for Button
  * @param  FGPIO_Type  FGPIOx (FGPIOA ,FGPIOB,FGPIOC,FGPIOD,FGPIOE) for buuton         
  		    FGPIO_Type  FGPIOy (FGPIOA ,FGPIOB,FGPIOC,FGPIOD,FGPIOE) for led 
		    Pin_state_Button : Pin selection for button
            Pin_state_Led    : Pin selection for led
	@retval none
  */
		
void DRIVER_LED_Toggle(FGPIO_Type* FGPIOx,FGPIO_Type* FGPIOy,uint32_t Pin_state_Button,uint32_t Pin_state_Led)
{
	
	if(HAL_GPIO_Read_Pin(FGPIOx,Pin_state_Button) == 0)
	{		  
		Delay(700);	
		
		while(HAL_GPIO_Read_Pin(FGPIOx,Pin_state_Button) == 0)
		{
				/*If held down then Do nothing */
		}
		
		u8status = ~u8status;
		
		HAL_GPIO_Write_Pin(FGPIOx,FGPIOy,Pin_state_Led,u8status);

	}	  
	
}
