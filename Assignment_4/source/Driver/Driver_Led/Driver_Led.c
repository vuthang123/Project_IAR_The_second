#include "Driver_Led.h"
#include "HAL_PORT.h"
#include "HAL_GPIO.h"
#include "HAL_CLOCK.h"
#include "MKE16Z4.h"
#include "HAL_LPIT.h"

/*******************************************************************************
 * Code
 ******************************************************************************/
/**
  * @brief  Initialization for Led
  * @param PORT_Type (PORTx ,PORTy,PORTz) for pin led          
  * @retval 0 : SUCCESS
			1 : ERROR
  */
DRIVER_LED_Erorr DRIVER_LED_init(PORT_Type* PORTx,PORT_Type* PORTy,PORT_Type* PORTz)
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
	/************************Enable clock PORTB************************/

	/*select mode gpio*/
	if(HAL_PORT_Select_Mode(PORTy,LED_GREEN,Mode_Gpio) != 0)
	{
		E_Retval = DRIVER_LED_FAIL;	
	}
	/*config output*/
	if(HAL_GPIO_IO(FGPIOB,LED_GREEN1,HAL_GPIO_OUTPUT))
	{
		E_Retval = DRIVER_LED_FAIL;	
	}
	/*Setup defaut*/
	if(HAL_GPIO_Setup_Defaut(FGPIOB,LED_GREEN1))
	{
		E_Retval = DRIVER_LED_FAIL;	
	}
	/***********************Enable clock PORTD********************************/
	
		/*cHECK ENABLE CLOCK PORT  D*/
	if (HAL_CLOCK_Init(PCC_PORTD_INDEX,PCC_PORTD_CGC_D) != 0)
	{
		E_Retval = DRIVER_LED_FAIL;	
	}
	/*select mode gpio*/
	if(HAL_PORT_Select_Mode(PORTz,LED_BLUE,Mode_Gpio) != 0)
	{
		E_Retval = DRIVER_LED_FAIL;	
	}
	/*config output*/
	if(HAL_GPIO_IO(FGPIOD,LED_BLUE1,HAL_GPIO_OUTPUT))
	{
		E_Retval = DRIVER_LED_FAIL;	
	}
	/*Setup defaut*/
	if(HAL_GPIO_Setup_Defaut(FGPIOD,LED_BLUE1))
	{
		E_Retval = DRIVER_LED_FAIL;	
	}
	
	return E_Retval;
	

}
/*******************************************************************************
 * EOF
 ******************************************************************************/


