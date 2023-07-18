#include "Driver_Button.h"
#include "HAL_GPIO.h"





/*******************************************************************************
 * Code
 ******************************************************************************/
/**
  * @brief  Initialization for Button
  * @param PORT_Type (PORTA ,PORTB,PORTC,PORTD,PORTE)         
  * @retval 0 : SUCCESS
			1 : ERROR
  */
DRIVER_BUTTON_Erorr DRIVER_BUTTON_init(PORT_Type* PORTx)
{
	
	DRIVER_BUTTON_Erorr E_Retval = DRIVER_BUTTON_SUCCESS ;
	
	/*cHECK ENABLE CLOCK PORT  D*/
	if (HAL_CLOCK_Init(PCC_PORTD_INDEX,PCC_PORTD_CGC) != 0)
	{
		E_Retval = DRIVER_BUTTON_FAIL;	
	}
	
	/*select mode gpio */
	if(HAL_PORT_Select_Mode(PORTx,BUTTON_SW2,Mode_Gpio) != 0)
	{
		E_Retval = DRIVER_BUTTON_FAIL;	
	}
	
	/*pull enable*/
	if(HAL_PORT_Select_Pull_Enable(PORTx,BUTTON_SW2,PULL_ENABLE))
	{
		E_Retval = DRIVER_BUTTON_FAIL;	
	}
	
	/*pull up */
	if(HAL_PORT_Select_Pull_Mode(PORTx,BUTTON_SW2,PULL_UP))
	{
		E_Retval = DRIVER_BUTTON_FAIL;	
	}
	/*config input*/
	if(HAL_GPIO_IO(FGPIOD,BUTTON,HAL_GPIO_INPUT))
	{
		E_Retval = DRIVER_BUTTON_FAIL;	
	}

	return E_Retval;
}


